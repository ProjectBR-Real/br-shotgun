# Buckshot Roulette Shotgun

Seeed XIAO ESP32C3 を使用して、Wi-Fi 経由で制御されるショットガン（の模型）を操作するためのファームウェアです。

ESP32C3 は Wi-Fi サーバーとして動作します。

## 必要なもの

### ハードウェア

- Seeed XIAO ESP32C3

### ソフトウェア

- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO IDE extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide)

## セットアップ

1.  このリポジトリをクローンまたはダウンロードします。
2.  VSCode でプロジェクトフォルダを開き、PlatformIO 拡張機能がインストールされていることを確認してください。
3.  Wi-Fi の SSID とパスワードを設定するために、`include/` ディレクトリに `config.h` という名前のファイルを作成します。
4.  `include/config.h` に以下の内容を記述し、ご自身の Wi-Fi 環境に合わせて `YOUR_WIFI_SSID` と `YOUR_WIFI_PASSWORD` を書き換えてください。

    ```cpp
    // filepath: include/config.h
    #pragma once

    const char* ssid = "YOUR_WIFI_SSID";
    const char* password = "YOUR_WIFI_PASSWORD";
    ```

## ビルドと書き込み

1.  Seeed XIAO ESP32C3 をコンピュータに接続します。
2.  PlatformIO のインターフェース（サイドバーのエイリアン/アリの頭のアイコン）を開きます。
3.  `Project Tasks` -> `seeed_xiao_esp32c3` -> `Upload` を選択して、コンパイルとファームウェアの書き込みを実行します。

## 使い方

ファームウェアが書き込まれると、ESP32C3 は設定された Wi-Fi に接続し、IP アドレスをシリアルモニターに出力します。

PC や他のデバイスから TCP クライアントを使用して、ポート `8080` で ESP32C3 に接続し、コマンドを送信します。

### コマンド

- `FIRE:<shellType>`: ショットガンを発砲させます。`<shellType>` の部分には `LIVE` や `BLANK` などを指定できます（現在のコードではこの文字列はログ出力にのみ使用されます）。
  - **例:** `FIRE:LIVE`

コマンドが正常に処理されると、デバイスは `DONE` という文字列を返信します。

## コードについて

主要なロジックは [`src/main.cpp`](src/main.cpp) に記述されています。

- `setup()`: Wi-Fi への接続とサーバーの初期化を行います。
- `loop()`: クライアントからの接続を待ち受け、データを受信してコマンドを解釈・実行します。

プロジェクトの設定は [`platformio.ini`](platformio.ini) ファイルで管理されています。
