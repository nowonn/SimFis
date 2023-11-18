def add_newline_after_21_commas():
    with open('input.txt', 'r') as file:
        data = file.read()
    data = data.split(',')
    new_data = []
    for i in range(0, len(data), 21):
        new_data.append(','.join(data[i:i+21]))
    with open('output.txt', 'w') as file:
        file.write(',\n'.join(new_data))

add_newline_after_21_commas()
