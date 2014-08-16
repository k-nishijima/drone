# Arduino <-> Raspberry Pi シリアルインターフェイス仕様

### ラズパイを親、Arduinoを子とする。

## 移動に関する仕様

親→子へのリクエスト：

* forward:nnnn
* back:nnnn
* stop
* left:nnnn
* right:nnnn

nnnn = 数字でミリ秒を指定

例： forward:5000 = 5千ミリ秒前進



## GPSに関する仕様

親→子へのリクエスト：

* location

（2秒待って）
レスポンス：GPSから返ってきた生データを1行返す

