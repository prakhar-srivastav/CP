import pandas as pd
import argparse
import requests
import random

def get_solved_problems_by_user(user,count_limit = 100000):
    url = 'https://codeforces.com/api/user.status?handle={}&from=1&count={}'
    r = requests.get(url.format(user,count_limit))
    info = r.json()
    submissions = info['result']
    status = info['status']
    if status != 'OK':
        raise

    problem_list = {}

    for submission in submissions:
        id = submission['id']

        verdict = submission.get('verdict','WA')
        if verdict != 'OK':
            continue
        problem_name = submission['problem']['name']
        contest_id = submission['problem']['contestId']
        problem_id_in_contest = submission['problem']['index']
        problem_key = "{}_{}".format(str(contest_id),problem_id_in_contest)
        tag_list = submission['problem']['tags']
        tag_str = ('|').join(tag_list)
        problem_rating =  submission['problem'].get('rating',-999)
        if problem_name not in problem_list.keys():
            problem_list[problem_name] = {'tags': tag_str,'rating': problem_rating, 'problem_key': problem_key}         

    return problem_list 


def get_link(key):
    url = 'https://codeforces.com/problemset/problem/{}/{}'
    contest, problem_id = key.split('_')
    return url.format(contest,problem_id)


def print_suggestion(problems):
    import pdb; pdb.set_trace()
    random_key = random.choice([key for key in problems.keys()])
    print("Here is the suggestion: {}".format(get_link(problems[random_key]['problem_key'])))


def print_rating_distribution(diff_problems):
    rating_dict = {}

    for key,value in diff_problems.items():
        if value['rating'] in rating_dict.keys():
            rating_dict[value['rating']] = rating_dict[value['rating']] + 1
        else:
            rating_dict[value['rating']] = 1

    for key in sorted(rating_dict.keys()):
        value = rating_dict[key]
        print("Rating: {}, Count: {}".format(str(key),str(value)))


def generate_diff_csv(user_a, user_b):
    user_a_solved_problems = get_solved_problems_by_user(user_a)
    user_b_solved_problems = get_solved_problems_by_user(user_b)
    diff_problems = {}
    for key in user_a_solved_problems.keys():
        if key in user_b_solved_problems.keys():
            continue
        else:
            diff_problems[key] = user_a_solved_problems[key]

    problem_key = []
    rating = []
    tags = []
    link = []
    for key, problem_info in diff_problems.items():
        problem_key.append(key)
        tags.append(problem_info['tags'])
        link.append(get_link(problem_info['problem_key']))
        rating.append(problem_info['rating'])

    print("Total Problem Solved by {}: {}".format(user_a,str(len(user_a_solved_problems))))
    print("Total Problem Solved by {}: {}".format(user_b,str(len(user_b_solved_problems))))
    print("Total Problem Solved by {} but not by {}: {}".format(user_a, user_b,str(len(diff_problems))))
    print("___________________________________________________")
    print_rating_distribution(diff_problems)
    print_suggestion(diff_problems)

    df = pd.DataFrame({'problem': problem_key, 'problem_url': link, 'rating': rating, 'tags': tags})
    df.to_csv('unsolved_problem.csv', index = False)


if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='Get User Information')
    parser.add_argument('user_a', type=str, 
                        help='User Set A')
    parser.add_argument('user_b', type=str,
                        help='User Set B')
    args = parser.parse_args()
    generate_diff_csv(args.user_a, args.user_b)
