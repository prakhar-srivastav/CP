import pandas as pd
import argparse
import requests


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
		try:
			id = submission['id']

			verdict = submission['verdict']
			if verdict != 'OK':
				continue
			problem_name = submission['problem']['name']
			contest_id = submission['problem']['contestId']
			problem_id_in_contest = submission['problem']['index']
			problem_key = "{}_{}".format(str(contest_id),problem_id_in_contest)
			tag_list = submission['problem']['tags']
			tag_str = ('|').join(tag_list)
			problem_rating =  submission['problem']['rating']
			if problem_name not in problem_list.keys():
				problem_list[problem_name] = {'tags': tag_str,'rating': problem_rating, 'problem_key': problem_key}			
		except:
			print(submission)
			print("USER =",user)
	
	return problem_list	


def get_link(key):
	url = 'https://codeforces.com/problemset/problem/{}/{}'
	contest, problem_id = key.split('_')
	return url.format(contest,problem_id)


def generate_diff_csv(user_a, user_b):
	user_a_solved_problems = get_solved_problems_by_user(user_a)
	user_b_solved_problems = get_solved_problems_by_user(user_b)
	problem_key = []
	rating = []
	tags = []
	link = []
	for key, problem_info in user_a_solved_problems.items():
		if key in user_b_solved_problems.keys():
			continue
		problem_key.append(key)
		tags.append(problem_info['tags'])
		link.append(get_link(problem_info['problem_key']))
		rating.append(problem_info['rating'])

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
