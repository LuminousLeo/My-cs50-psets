from flask import Flask, render_template, request

app = Flask(__name__)


COLORS = [
    'red',
    'blue'
]

@app.route('/', methods=['GET', 'POST'])
def index():
    color = request.form.get('color')
    if request.method == 'GET':
        return render_template('index.html', colors=COLORS)
    if color in COLORS:
        print('Form submitted!')
        return render_template('color.html', color=color)
    return render_template('failure.html')
