#include <stdio.h>
#include <stdlib.h>
#include <math.h> // べき乗
#include <string> // C++　文字列
#include <iostream> // 表示
#include <vector> // 配列
// 文字列中の漢数字をその最大値まで算用数字に変換可能。ゼロなし、千万、数字なしの問題を解決
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
	std::string keta_4_moji[] = {"","万","億","兆","京","垓"};
    std::string keta_moji[] = {"十","百","千"};
	//std::string keta_moji[] = {"","十","百","千","万","十","百","千","億","十","百","千","兆","十","百","千","京","十","百","千","垓","十","百","千"};
	std::string kanji_num[] = {"一","二","三","四","五","六","七","八","九",""};
	std::string target_moji[] = {"一","二","三","四","五","六","七","八","九","十","百","千","万","億","兆","京","垓"};
	
	//moji = keta_4_moji[1] + keta_moji[1]; //"・・・・加工前"; //連結方法
	//printf("kansu_before -> %s\n", moji.c_str());
// ループ　置換内容の追加から
//printf("array = %lu\n",sizeof(target_moji) / sizeof(target_moji[0]));

    // 文字列の右側に「digit_0_assist」を付ける
	for (int i = 0; i <= (sizeof(target_moji) / sizeof(target_moji[0]) - 1); i++) {
		moji = all_Replace(moji, target_moji[i], target_moji[i] + "digit_" + std::to_string(0) + "_assist");
	}
    // 文字列の左側の「digit_0_assist」を消す
	for (int i = 0; i <= (sizeof(target_moji) / sizeof(target_moji[0]) - 1); i++) {
		moji = all_Replace(moji, "digit_" + std::to_string(0) + "_assist" + target_moji[i], target_moji[i]);
	}

	//moji = all_Replace(moji, keta_moji[1], "ABC" + std::to_string(((10 % 4) + (int)(9 / 10)) * (int)pow(3,2)));
	for (int i = 0; i < (sizeof(keta_4_moji) / sizeof(keta_4_moji[0]) - 1); i++) {
		for (int j = i; j >= 0; j--) {
			for (int k = 0; k < (sizeof(kanji_num) / sizeof(kanji_num[0]) - 1); k++) {
				if ((i % 4) == 0) {
					moji = all_Replace(moji, , );
				} else {
					moji = all_Replace(moji, , );
				}	
			}
		}
//

	}
	std::cout << "kansu_after -> " + moji + keta_moji[2] + "後" << std::endl;
	// ketamojinosyori
	
	return moji + "後";
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