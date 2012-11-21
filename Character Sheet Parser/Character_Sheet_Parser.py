import os
import Image

filename = "consola22_2048x26.png"
im = Image.open(filename)
width, height = im.size

print "Image Size: (" + str(width) + "," + str(height) + ")"
print ""

chars = []  # Tuple of left and right x coordinates
colDelim = []
charWidth = []

left = -1    # Left limit of a character
right = -1   # Right limit of a character

for x in range(0, width):
    colColor = 1   # black=1 white=0

    for y in range(0, height):  # Traverse down the column
        coord = (x,y)
        pixel = im.getpixel(coord)

        # Determines if a row is solid black or if it is part of a character
        if pixel[0] != 0 and pixel[1] != 0 and pixel[2] != 0:
            colColor = 0
            break

    # If left has not been set, we're looking for a new character
    # The first non-black column is the left of the character
    if left == -1 and colColor == 0:
        left = x
    # If left has been set, we are looking for the first black column
    # This will be the right side of the character
    if left != -1 and colColor == 1:
        right = x
        # Store character width
        charWidth.append(right - left)
        # Convert to floats
        left = float(float(left) / float(width))
        right = float(float(right) / float(width))
        colDelim.append( (left, right) )
        left = -1   # Reset left
        right = -1  # Reset right

# Output the data into a file in the correct format
# Read characters from ordered list
charfile = open("charlist_ascii.txt", 'r')	# Open the file containing a list of characters the sheet contains, in order
chars = charfile.read()		# Store list of chars
charfile.close()

# Create new file for text data
outFilename = os.path.splitext(filename)[0]
outFilename = outFilename + ".txt"
fout = open(outFilename, 'w')

# Write information to the new file
colIndex = 0
for index, c in enumerate(chars):
    if (colIndex < len(colDelim)):
        fout.write(str(31 + index) + " ")
        fout.write(chars[index] + " ")

        fout.write(str(colDelim[index][0]) + " ")
        fout.write(str(colDelim[index][1]) + " ")
        colIndex += 1

        fout.write(str(charWidth[index]))
        fout.write("\n")

fout.close()

print("Done")
raw_input()