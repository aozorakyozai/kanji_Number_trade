// 文字列中の漢数字をその最大値まで算用数字に変換可能。ゼロがないこと、千と万の処理、桁の前に数字がないの問題をクリア
#include <stdio.h>
#include <stdlib.h>
#include <string> // C++　文字列
#include <iostream> // 表示

std::string kanji_num_trade(std::string moji); //説明は、下記sample参照　ポインタで返す予定
std::string all_Replace(std::string std, std::string target_std, std::string change_std); //すべて置換

int main() {
	std::string sample = "たとえば、「百垓百一京百十二兆二百億二百一万二百二十二」の中の「百」は六通りの置換をする";//入力

	printf("main_before -> %s\n", sample.c_str());

	std::string num_moji = kanji_num_trade(sample); // 置換

	printf("main_after -> %s\n", num_moji.c_str()); //出力　.c_str()は先頭アドレス

	return 0;
}    

std::string kanji_num_trade(std::string moji) //cでも作る予定
{
	//char keta_moji[][ 6 ] = {"十","百","千"};
	#define keta_moji_ARRAY_SIZE 3
	#define KETA_4 4 //4ケタごとに出現する[keta_4_moji]から総桁数を求める
	#define KETA_0 1 //[keta_4_moji]の処理上の0ケタ目の数をマイナスする

	std::string keta_4_moji[] = {"","万","億","兆","京","垓"};
    std::string keta_moji[] = {"十","百","千"};
	std::string kanji_num[] = {"一","二","三","四","五","六","七","八","九",""};

	std::string target_moji[] = {"一","二","三","四","五","六","七","八","九","十","百","千","万","億","兆","京","垓"};

//std::string target_moji[] = keta_4_moji[] + keta_moji[];
//printf("%s\n", target_moji[].c_str());
    // 文字列の右側に「digit_0_assist」を付ける
	for (int i = 0; i <= (sizeof(target_moji) / sizeof(target_moji[0]) - KETA_0); i++) {
		moji = all_Replace(moji, target_moji[i], target_moji[i] + "digit_" + std::to_string(0) + "_assist");
	}
    // 文字列の左側の「digit_0_assist」を消す
	for (int i = 0; i <= (sizeof(target_moji) / sizeof(target_moji[0]) - 1); i++) {
		moji = all_Replace(moji, "digit_" + std::to_string(0) + "_assist" + target_moji[i], target_moji[i]);
	}

	for (int i = 0; i < ( (sizeof(keta_4_moji) / sizeof(keta_4_moji[0]) - 1 ) * KETA_4 + keta_moji_ARRAY_SIZE); i++) {
		for (int j = i; j >= 0; j--) {
			for (int k = 0; k < (sizeof(kanji_num) / sizeof(kanji_num[0])); k++) {
				std::string before_trade;
				std::string after_trade;
				if ((i % KETA_4) == 0) {
					before_trade = kanji_num[k] + keta_4_moji[i / KETA_4] + "digit_" + std::to_string(j) + "_assist";
					after_trade = "digit_" + std::to_string(i + 1) + "_assist" + std::to_string((k + 1) % 10) + std::string(i - j, '0');
				} else {
					before_trade = kanji_num[k] + keta_moji[(i % KETA_4) - 1] + "digit_" + std::to_string(j) + "_assist";
					after_trade = "digit_" + std::to_string(i + 1) + "_assist" + std::to_string((int)((k + 1) / 10) + ((k + 1) % 10)) + std::string(i - j, '0');
				}	
				moji = all_Replace(moji, before_trade, after_trade);
			}
		}
	}




	return moji;
}

std::string all_Replace(std::string std1, std::string target_std, std::string change_std)
{
    std::string::size_type  Pos(std1.find(target_std));

    while(Pos != std::string::npos)
    {
        std1.replace(Pos, target_std.length(), change_std);
        Pos = std1.find(target_std, Pos + change_std.length());
    }

    return std1;
}