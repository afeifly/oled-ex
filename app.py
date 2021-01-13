from flask import Flask,render_template,request
from flask_cors import *
from flask import jsonify
import show_text
import restclient
import datetime
#app = Flask(__name__, static_folder="/templates/build/static", template_folder="/templates/build")
app = Flask(__name__, static_url_path='/static', template_folder='templates')
CORS(app,supports_credentials=True)

# TODO make global 
messageIndex = -1 
messageTxt = None
messageTime = datetime.datetime.now()

@app.route("/")
def hello():
    return render_template('/index.html') 
@app.route("/test")
def test():
    return render_template('/index.html') 


@app.route("/updatemsg",methods=['GET','POST'])
def updatemsg():
  msg = request.form['msg']
  global messageIndex 
  global messageTxt
  messageIndex += 1
  messageTxt = msg
  return jsonify({'status' : 'ok'}), 202

  
@app.route("/fetch")
def fetch():
    #index = request.form['index']
    index = request.args.get('index')
    print('index ='+str(index)+ ' msgindex='+str(messageIndex))
    if messageIndex < 0 or str(index) == str(messageIndex):
      return jsonify({'status' : 'ok'}), 202
    else :
      return jsonify(
        index=messageIndex,
        msg=messageTxt,
        time=messageTime
      )


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
