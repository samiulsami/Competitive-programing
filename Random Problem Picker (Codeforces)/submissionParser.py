def parseSubmissions(submissions):
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
