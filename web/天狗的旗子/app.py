from flask import Flask, request, send_file
app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'Simping Detected!'

@app.route('/robots.txt')
def robots_txt():
        return send_file("robots.txt")

@app.route('/feasgsdrgvsefzergvsdfvsvgswgewrf')
def flag():
    if request.headers.get('X-Forwarded-For', "") != 'localhost':
        return 'only localhost can access'
    return 'tjctf{fORW@Rd_Y0ur_f1a6}'

@app.route('/flag')
def fake_flag():
    return 'tjctf{i_am_not_flag}'

if __name__ == '__main__':
    app.run(debug=False, host='0.0.0.0', port=38089)
