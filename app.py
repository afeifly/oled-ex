from flask import Flask,render_template,request
from flask_cors import *
import show_text
import restclient
#app = Flask(__name__, static_folder="/templates/build/static", template_folder="/templates/build")
app = Flask(__name__, static_url_path='/static', template_folder='templates')
CORS(app,supports_credentials=True)
@app.route("/")
def hello():
    return render_template('/index.html') 
@app.route("/test")
def test():
    return render_template('/index.html') 

@app.route("/sendmsg",methods=['GET','POST'])
def sendmsg():
    msg = request.form['msg']
    print("message = "+msg)
    display = request.form['options']
    print("display option = "+display)
    if int(display)==0 :
        print("No need display")
        restclient.send(msg)
    else :
        show_text.send(msg)
        restclient.send(msg)
    return 'ok'
if __name__ == '__main__':
    app.run(host='0.0.0.0',debug=True)
