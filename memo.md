## Raspberry Pi側

* Python RPC Libraryを入れる https://mbed.org/cookbook/Interfacing-with-Python

* 1箇所修正（どこ？？） http://blog.goo.ne.jp/roboz80/e/5dc5a26535b2dd42b7820ec993c284d1

* こんな感じでシリアルプログラミングしましょう http://nwpct1.hatenablog.com/entry/2013/10/18/124844

## ラズパイ側の無線のIPアドレスを取得する方法

* http://openrtm.org/openrtm/ja/node/266 の「ホスト名でリモート接続する」というところを見て設定
* これで上手く行かなければこっち http://catmoney.hatenablog.com/entry/20140201
* 最悪これでも http://www.raspberrypi.org/forums/viewtopic.php?f=82&t=26462

西島のラズパイ

wlan0     Link encap:イーサネット  ハードウェアアドレス b0:c7:45:ed:05:b4 
          inetアドレス:192.168.55.37 ブロードキャスト:192.168.63.255  マスク:255.255.240.0

## mbed側

* mbed RPC Over Serialを入れる
* http://mbed.org/users/okini3939/notebook/RPC_jp/
* →とその前に、mbed-rpcライブラリをインポートしないと行けないとのこと。。
* https://mbed.org/teams/mbed-official/code/mbed-rpc/

* https://mbed.org/cookbook/Interfacing-with-Python

* GPSデータを読み込むコマンドを、RPCに対応させる
* http://mbed.org/users/okini3939/notebook/RPC_jp/

## Windowsでシリアル通信

* http://mbed.org/users/weed/notebook/how_to_communicate_by_serial_port_on_windows7/


## 諦めてArduinoでやろう

* EM-406Aというモジュールなのかな？
* http://tokyo2show.co.jp/news/?p=25
* 配線 http://www.instructables.com/id/Connecting-GPS-module-to-Arduino/?lang=ja
