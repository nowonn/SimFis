def replace_newlines(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    with open(filename, 'w') as file:
        for i, line in enumerate(lines):
            file.write(line.rstrip('\n') + ',')  # replace new line with comma

# Call the function with the filename
replace_newlines('input.txt')
