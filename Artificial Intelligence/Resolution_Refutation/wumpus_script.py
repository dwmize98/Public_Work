import sys 

length = 4 


#rows
# for first in range(length):
#     for second in range(length):
#             hold = "(or (not W" + str(first + 1) + str(second + 1)
#             for row in range(length):
#                 for col in range(length):
#                     if row >= first and col >= second:
#                         if row != first or col != second:
#                             print(hold + ") (not W" + str(row + 1) + str(col + 1) + "))")


# for first in range(length):
#     for second in range(length):
#         #hold = "(or (not B" + str(first + 1) + str(second + 1)
#         #print(hold + ") (not P" + str(row + 1) + str(col + 1) + "))")
#         print("(or (not P" + str(first + 1) + str(second + 1) + ") (safe" + str(first + 1) + str(second + 1) + "))")

for first in range(length):
    for second in range(length):
            hold = "(or (not S" + str(first + 1) + str(second + 1) + ")"
            if (first + 2 < 5):
                hold += " W" + str(first + 2) + str(second + 1)
            if (first > 0):
                hold += " W" + str(first) + str(second + 1)
            if (second + 2 < 5):
                hold += " W" + str(first + 1) + str(second + 2)
            if (second > 0):
                hold += " W" + str(first + 1) + str(second)
            print(hold + ")")
            

