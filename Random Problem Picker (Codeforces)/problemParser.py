from problemConstraints import *

def parseProblems(problems, solved):
    urlList = []
    for problem in problems:
        contestId = str(problem["contestId"])
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
