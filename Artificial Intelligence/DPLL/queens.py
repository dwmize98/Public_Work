import sys

length = int(sys.argv[1])


#rows
for row in range(length):
    column = "(or"
    for col in range(length):
        column += " Q"
        column += str(row+1)
        column += str(col+1)
        if col == length - 1:
            column += ")"
            clause = ' '.join(column)
            print(column)
        for pos in range(length - col):
            if col + 1 < length and col+1 != col+pos+1:
                print ("(or (not Q" + str(row+1) + str(col+1) + ") (not Q" + str(row+1) + str(col+pos+1) + "))")

#columns
for col in range(length):
    for row in range(length):
        for pos in range(length - row):     
            if row + 1 < length and row+1 != row+pos+1:
                print ("(or (not Q" + str(row+1) + str(col+1) + ") (not Q" + str(row+pos+1) + str(col+1) + "))")

#diagonal (left to right)
for row in range(length):
    for col in range(length):
        for pos in range(length - col):
            if col + 1 < length and col+1 != col+pos+1 and row+1 != row+pos+1 and row+pos < length and col+pos < length:
                print ("(or (not Q" + str(row+1) + str(col+1) + ") (not Q" + str(row+pos+1) + str(col+pos+1) + "))")


#diagonal (top to bottom)
for row in range(length):
    for col in range(length):
        for pos in range(length - col):
            if col + 1 < length and col+1 != col+pos+1 and row+1 != row-pos+1 and row-pos+1 > 0 and col+pos < length:
                print ("(or (not Q" + str(row+1) + str(col+1) + ") (not Q" + str(row-pos+1) + str(col+pos+1) + "))")





