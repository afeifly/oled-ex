from flask import Flask,render_template,request
import show_text
app = Flask(__name__)

@app.route("/")
def hello():
    return render_template('index.html') 

@app.route("/sendmsg",methods=['GET','POST'])
def sendmsg():
    msg = request.form['msg']
    print(msg)
    show_text.send(msg)
    return render_template('index.html') 

if __name__ == '__main__':
    app.run(host='0.0.0.0',debug=True)
