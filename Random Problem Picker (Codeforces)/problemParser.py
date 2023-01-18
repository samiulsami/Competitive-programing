from parserLibs import *
import submissionParser

def parseProblems(curdate):
    solved = submissionParser.parseSubmissions(curdate)
    problems = {}
    reloadProblems = True
    
    if path.exists("parsedData\\problems.json"):
        tmpProblems = {}
        with open("parsedData\\problems.json","r") as read_file:
            tmpProblems = json.load(read_file)
        parseDate = tmpProblems["parseDate"]
        print("Problems last parsed on " + parseDate + "\nReload Problems? (Y/N)")
        
        inpChar = input()
        if inpChar=='Y' or inpChar=='y':
            reloadProblems = True
        else:
            problems = tmpProblems["data"]
            reloadProblems = False

    if reloadProblems:
        print("Fetching problems...")
        response = requests.get("https://codeforces.com/api/problemset.problems")
        problems = json.loads(response.text)["result"]["problems"]
        tmp = {}
        tmp["parseDate"] = curdate
        tmp["data"] = problems
        with open("parsedData\\problems.json","w+") as write_file:
            json.dump(tmp, write_file)
            
    urlList = []
    for problem in problems:
        contestId = str(problem["contestId"])
        if int(contestId)<915: 
            continue
            
        if len(contestId)==0:
            continue;
        
        if "rating" not in problem:
            continue
        
        rating = problem["rating"]
        if not (rating >= minRating and rating <= maxRating):
            continue

        tagsOK = True
        if len(includedTags)>0:
            if "tags" in problem:
                for tag in includedTags:
                    if tag not in problem["tags"]:
                        tagsOK = False
            else:
                tagsOK = False

        if len(excludedTags)>0:
            if "tags" in problem:
                for tag in excludedTags:
                    if tag in problem["tags"]:
                        tagsOK = False
        
        if not tagsOK:
            continue
        
        index = str(problem["index"])
        ProblemLink = "https://codeforces.com/problemset/problem/"+contestId+"/"+index
        if ProblemLink in solved:
            continue
        
        tmp = []
        tmp.append(ProblemLink)
        tmp.append(problem["name"])
        tmp.append(str(rating))
        if "tags" in problem:
            tmp.append(str(problem["tags"]))
        urlList.append(tmp)

    return urlList
