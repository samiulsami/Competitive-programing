import random
import time
import pyperclip
import os
from datetime import date

from problemConstraints import *
import problemParser

random.seed(time.time())
_clear_console = True
curdate = str(date.today().strftime("%B %d, %Y"))
urlList = problemParser.parseProblems(curdate)

while len(urlList)>0:
    if _clear_console:
        os.system("CLS")
    print("Rating range: " + str(minRating) + " to " + str(maxRating)+ "\n")
    if len(includedTags)>0:
        print("Included Tags: " + str(includedTags) + "\n")
    if len(excludedTags)>0:
        print("Excluded Tags: " + str(excludedTags) + "\n")

    ind = random.randint(0,len(urlList)-1)
    tmp = urlList[ind]
    print("-----------------------------------------------------------\n")
    print("Problem Name: " + tmp[1])
    
    if showRating:
        print("Rating: " + tmp[2])
    if showTags:
        print("Tags: " + tmp[3])

    print("Link: " + tmp[0])
    pyperclip.copy(tmp[0])
    print("\n             **LINK COPIED TO CLIPBOARD**\n")

    urlList.remove(tmp)
    if len(urlList)==0:
       break

    print(str(len(urlList)) + " Problems remaining\nPress 'Enter' to pick the next problem\n")
    input()

print("No more problems left\n")
input()
