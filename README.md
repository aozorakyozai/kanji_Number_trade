＜文字列中の漢数字を算用数字に変換する＞

・unsigned int long long　の範囲より大きな範囲を変換できる。計算によらずに置換を使うので最大値（無量大数）まで変換できる。

・置換を使うため文字列中の複数の漢数字を同時に変換できる。

・漢数字を置換するときの問題点は、①ゼロがないこと、②千と万の処理が違う、③桁の前に数字がない場合がある（Ex．千百十二 -> 1112）、という３点。
