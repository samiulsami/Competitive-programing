import json
import os.path
from os import path
import requests
import random
import time
import pyperclip
from datetime import date
#import files
from problemConstraints import *
import submissionParser
import problemParser

random.seed(time.time())
curdate = str(date.today().strftime("%B %d, %Y"))
_clear_console = True
##########################################################################

reloadSubmissions = True
reloadProblems = True
submissions = {}
problems = {}

if path.exists("submissions.json"):
    tmpSubmissions = {}
    with open("submissions.json","r") as read_file:
        tmpSubmissions = json.load(read_file)
    parseDate = tmpSubmissions["parseDate"]
    print("Submissions for user: \"" + tmpSubmissions["username"] +"\" last parsed on " + parseDate + "\nReload Submissions? (Y/N)")

    inpChar = input()
    if inpChar=='Y' or inpChar=='y':
        reloadSubmissions = True
    else:
        submissions = tmpSubmissions["data"]
        reloadSubmissions = False
  
if path.exists("problems.json"):
    tmpProblems = {}
    with open("problems.json","r") as read_file:
        tmpProblems = json.load(read_file)
    parseDate = tmpProblems["parseDate"]
    print("Problems last parsed on " + parseDate + "\nReload Problems? (Y/N)")
    
    inpChar = input()
    if inpChar=='Y' or inpChar=='y':
        reloadProblems = True
    else:
        problems = tmpProblems["data"]
        reloadProblems = False


#Create a dictionary of all accepted submissions
if reloadSubmissions:
    print("Fetching submissions...")
    response = requests.get("https://codeforces.com/api/user.status?handle="+username)
    submissions = json.loads(response.text)["result"]
    tmp = {}
    tmp["parseDate"] = curdate
    tmp["data"] = submissions
    tmp["username"] = username
    with open("submissions.json","w+") as write_file:
        json.dump(tmp, write_file)

solved = submissionParser.parseSubmissions(submissions)

#Create a list of problems that fit the given constraints
if reloadProblems:
    print("Fetching problems...")
    response = requests.get("https://codeforces.com/api/problemset.problems")
    problems = json.loads(response.text)["result"]["problems"]
    tmp = {}
    tmp["parseDate"] = curdate
    tmp["data"] = problems
    with open("problems.json","w+") as write_file:
        json.dump(tmp, write_file)
        
urlList = problemParser.parseProblems(problems, solved)



#Start randomly picking problems
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
    urlList.remove(tmp)
    if len(urlList)==0:
       break
    
    pyperclip.copy(tmp[0])
    print("**LINK COPIED TO CLIPBOARD**\n")
    print(str(len(urlList)) + " Problems remaining\nPress 'Enter' to pick the next problem\n")
    input()

print("No more problems left\n")
input()
