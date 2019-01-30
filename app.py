from flask import Flask,render_template,request
import show_text
import restclient
app = Flask(__name__)

@app.route("/")
def hello():
    return render_template('main.html') 

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
    return render_template('main.html') 

if __name__ == '__main__':
    app.run(host='0.0.0.0',debug=True)
