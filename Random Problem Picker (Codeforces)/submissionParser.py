from parserLibs import *

def parseSubmissions(curdate):
    submissions = {}
    reloadSubmissions = True
     
    if path.exists("parsedData\\submissions.json"):
        tmpSubmissions = {}
        with open("parsedData\\submissions.json","r") as read_file:
            tmpSubmissions = json.load(read_file)
        parseDate = tmpSubmissions["parseDate"]
        print("Submissions for user: \"" + tmpSubmissions["username"] +"\" last parsed on " + parseDate + "\nReload Submissions? (Y/N)")

        inpChar = input()
        if inpChar=='Y' or inpChar=='y':
            reloadSubmissions = True
        else:
            submissions = tmpSubmissions["data"]
            reloadSubmissions = False
       
    if reloadSubmissions:
        print("Fetching submissions...")
        response = requests.get("https://codeforces.com/api/user.status?handle="+username)
        submissions = json.loads(response.text)["result"]
        tmp = {}
        tmp["parseDate"] = curdate
        tmp["data"] = submissions
        tmp["username"] = username
        with open("parsedData\\submissions.json","w+") as write_file:
            json.dump(tmp, write_file)

    solved = {}
    for submission in submissions:
        if "verdict" not in submission:
            continue
        if not submission["verdict"] == "OK":
            continue
        if "rating" not in submission["problem"]:
            continue
        ProblemLink = "https://codeforces.com/problemset/problem/"+str(submission["problem"]["contestId"])+"/"+str(submission["problem"]["index"])
        solved[ProblemLink]=True
    return solved
