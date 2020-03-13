from flask import Flask,render_template,request
from flask_cors import *
import mytts

app = Flask(__name__, static_url_path='', static_folder='build')
CORS(app,supports_credentials=True)
@app.route("/")
def hello():
    return app.send_static_file('index.html') 
@app.route("/test")
def test():
    return render_template('/index.html') 

@app.route("/sendmsg",methods=['GET','POST'])
def sendmsg():
    msg = request.form['msg']
    print("message = "+msg)
    mytts.speaker(msg)
    return 'ok'
if __name__ == '__main__':
    app.run(host='0.0.0.0',debug=True)
