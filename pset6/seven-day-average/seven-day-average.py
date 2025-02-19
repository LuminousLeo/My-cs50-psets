import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    new_cases = dict()
    previous_cases = dict()

    for row in reader:
        state = row['state']
        date = row['date']
        case = int(row['cases'])

        if state not in previous_cases:
            previous_cases[state] = case
            new_cases[state] = []
        else:
            new_case = case - previous_cases[state]
            previous_cases[state] = case

            if len(new_cases[state]) >= 14:
                new_cases[state].pop(0)
            new_cases[state].append(new_case)

    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    counter = len(states)
    for i in range(counter):
        this_week = sum(new_cases[states[i]][7:13]) / 7
        previous_week = sum(new_cases[states[i]][0:6]) / 7

        try:
            percentage = (this_week- previous_week) / previous_week
        except ZeroDivisionError:
            print(f'{states[i]}: Cannot divide by zero')
        else:
            print(f'{states[i]} had a 7-day average of {round(this_week)} and an increase of {round(percentage)}%.')


main()