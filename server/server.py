from flask import Flask
from flask import request

app = Flask(__name__)

@app.route("/v0/get", methods=['GET'])
def dadosget():
    print("me chamaram por get")
    return "<p>GET ok</p>"


@app.route("/v0/dados", methods=['POST'])
def dados():
    print("Função chamada no post")
    print(request.args)
    print(request.get_json())
    print(request.headers.get("Content-Type"))
    print(request.headers.get("x-api-key"))
    return "<p>POST ok</p>"


if __name__ == '__main__':
   app.run()

#python -m flask --app=server run --host=0.0.0.0