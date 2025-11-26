import cv2 as cv
import numpy as np

def rescaleFrame(frame, scale = 0.75):
    width = int(frame.shape[1] * scale)
    height = int(frame.shape[0] * scale)

    dimensions = (width, height)

    return cv.resize(frame, dimensions, interpolation=cv.INTER_AREA)

#convert board lines found into slope-intercept equation and find intersection points
def calcIntersectionPoints(lines):
    vertical = []
    horizontal = []
    
    # separate lines based on slope
    for ln in lines:
        dx = ln['x2'] - ln['x1']
        dy = ln['y2'] - ln['y1']

        # near-vertical
        if abs(dx) < 20:
            x = (ln['x1'] + ln['x2']) // 2
            vertical.append(x)
        # near-horizontal
        elif abs(dy) < 20:
            y = (ln['y1'] + ln['y2']) // 2
            horizontal.append(y)

    if len(vertical) != 2 or len(horizontal) != 2:
        print("ERROR: could not classify lines into 2 vertical + 2 horizontal")
        return (-1, -1)

    vertical.sort()
    horizontal.sort()

    # produce intersection points (all four)
    # top-left, top-right, bottom-left, bottom-right
    tl = (vertical[0], horizontal[0])
    tr = (vertical[1], horizontal[0])
    bl = (vertical[0], horizontal[1])
    br = (vertical[1], horizontal[1])

    return [bl, tl, br, tr]

#Line intersection helper function
def line_intersection(m1, b1, m2, b2):
    # If both lines are vertical or have the same slope, no intersection
    if m1 == m2:
        return (-1, -1)

    # Handle vertical lines
    if m1 is None:  # first line vertical
        x = b1
        y = m2 * x + b2
    elif m2 is None:  # second line vertical
        x = b2
        y = m1 * x + b1
    else:  # regular intersection
        x = (b2 - b1) / (m1 - m2)
        y = m1 * x + b1

    return (x, y)

#Read image (this path is absolute and can be changed), eventually it will read from the ros topic
img = cv.imread('/home/noah/roarm_ws_em0/tictactoe_cv/cv_clean.jpg') 
img = rescaleFrame(img, 0.12)

img2 = img.copy()
img_gray = img.copy()

#gray
img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

#dialtate
img = cv.dilate(img, (3,3), iterations=1)

#medianblur
img = cv.GaussianBlur(img, (3,3), 0)

#adaptive theshold
img = cv.adaptiveThreshold(img, 255, cv.ADAPTIVE_THRESH_MEAN_C, cv.THRESH_BINARY, 9, 17)

#canny edge detection
img = cv.Canny(img, 125, 175)

#find contours
contours, heirarchy = cv.findContours(img, cv.RETR_EXTERNAL, cv.CHAIN_APPROX_NONE)
cv.drawContours(img2, contours, -1, (255,0,125), 2)

#find other lines in photo (x's and O's)
lines = cv.HoughLinesP(img, rho=1, theta=np.pi/180, threshold=80, minLineLength=50, maxLineGap=70)

if lines is not None:
    for line in lines:
        x1, y1, x2, y2 = line[0]
        cv.line(img2, (x1, y1), (x2, y2), (85, 255, 0), 2)


# Assuming 'lines' is the output from HoughLinesP
merged_lines = []

#Merges any close or broken lines
for line in lines:
    x1, y1, x2, y2 = line[0]
    found = False

    for ml in merged_lines:
        # Merge lines if they are close in either x or y
        if (abs(ml['x1'] - x1) < 60 and abs(ml['y1'] - y1) < 40) or \
           (abs(ml['x2'] - x2) < 60 and abs(ml['y2'] - y2) < 40):
            found = True
            break

    if not found:
        merged_lines.append({'x1': x1, 'y1': y1, 'x2': x2, 'y2': y2})

colour = 20

# Draw the merged lines
for ml in merged_lines:
    cv.line(img2, (ml['x1'], ml['y1']), (ml['x2'], ml['y2']), (255-colour, (int)(colour / 2), colour), 2)
    colour += 40

print('num of merged lines: ')
print(len(merged_lines))


ints_pts = [
    (0, 0),
    (0, 0),
    (0, 0),
    (0, 0)
]

if (len(merged_lines) == 4):
   ints_pts = calcIntersectionPoints(merged_lines) # Create intersection points
else:
    print('ERROR: incorrect number of grid lines detected')

print("INTERSECTION POINTS RAW =", ints_pts)


#instantiate cropping points
pt1 = (0,0)
pt2 = (0,0)

#Forms the cropping rectangle
if ints_pts[0] != -1:  # make sure intersections were found
    pt1 = (int(ints_pts[1][0]), int(ints_pts[1][1]))
    pt2 = (int(ints_pts[2][0]), int(ints_pts[2][1]))
    cv.rectangle(img2, pt1, pt2, (255, 255, 255), 2)

width = int(pt2[0] - pt1[0])
height = int(pt2[1] - pt1[1])

#Instantiate the tic tac toe grid's bounding box coordinates
bb1 = ((int)(pt1[0] - width),(int)(pt1[1]-height))
bb2 = ((int)(pt2[0] + width),(int)(pt2[1]+height))
cv.rectangle(img2, bb1, bb2, (0, 0, 255), 2)

#Manually calculate the coordinates of the cells (with some offset for camera warp)
cells = []
cell_coords = [
    (bb1[0] - 10, bb1[1] - 10, ints_pts[1][0], ints_pts[1][1]),
    (ints_pts[1][0], bb1[1] - 10, ints_pts[2][0], ints_pts[1][1]),
    (ints_pts[2][0], bb1[1] - 10, bb2[0] + 10, ints_pts[1][1]),
    (bb1[0] - 10, ints_pts[1][1], ints_pts[1][0], ints_pts[2][1]),
    (pt1[0], pt1[1], pt2[0], pt2[1]),
    (ints_pts[2][0], ints_pts[1][1], bb2[0] + 10, ints_pts[2][1]),
    (bb1[0] - 10, ints_pts[2][1], ints_pts[1][0], bb2[1] + 10),
    (ints_pts[1][0], ints_pts[2][1], ints_pts[2][0], bb2[1] + 10),
    (ints_pts[2][0] + 10, ints_pts[2][1], bb2[0], bb2[1] + 10)   
]

# Make sure all coordinates are integers
cell_coords = [tuple(map(int, coords)) for coords in cell_coords]

cells = []

img_gray = cv.cvtColor(img_gray, cv.COLOR_BGR2GRAY)
img_gray = cv.medianBlur(img_gray, 5)


for (x1, y1, x2, y2) in cell_coords:
    cell = img_gray[y1:y2, x1:x2]
    cells.append(cell)


i = -1

#find and classify X and O within each cell
for cell in cells:  
    i += 1
    found = False

    #finds more contours within the cell
    contours2, hierarchy = cv.findContours(cell, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
    
    for cnt in contours2:
        area = cv.contourArea(cnt)
        
        if area > 15:  # ignore tiny noise
            # Circle detection
            circles = cv.HoughCircles(cell, cv.HOUGH_GRADIENT, 1, 25, param1=50, param2=10, minRadius=5, maxRadius=60)

            # X detection via HoughLines
            lines = cv.HoughLinesP(cell, 1, np.pi/180, threshold=20,
                                   minLineLength=10, maxLineGap=5)
            
            if lines is not None and len(lines) >= 2:
                print("X detected")
                found = True
                break
            elif circles is not None:
                print("O detected") 
                found = True
                break;   
    
    if not found: print("None Detected")    
    print("cell above ^^ = ")
    print(i)

cv.imshow('image', img)
cv.imshow('image2', img2)

for i, cell in enumerate(cells):
    cv.imshow(f"cell {i}", cell)

cv.waitKey(0)

cv.destroyAllWindows()
