#include <stdio.h>
#include <stdlib.h>
#include <string> // 文字列
#include <iostream> // 表示

std::string kanji_num_trade(std::string); //説明は、下記sample参照　ポインタで返す予定
std::string all_Replace(std::string, std::string, std::string); //すべて置換
std::string legal_doc(std::string); //　用途別　法律文書用
std::string irregular(std::string); // 例外処理

int main() {
	//std::string sample;
	//printf("漢数字を入力してください。\n");
	//std::scanf("%s", &sample);

	std::string sample = "Ex．「百垓百一京百十二兆二百億二百一万二百二十二」の中の「百」は六通りの置換がある。";//入力
	
	printf("main_before -> %s\n", sample.c_str());

	std::string num_moji = kanji_num_trade(sample); // 置換

	printf("main_after -> %s\n", num_moji.c_str()); //出力

	return 0;
}    

std::string kanji_num_trade(std::string moji) // 置換
{
	#define keta_moji_ARRAY_SIZE 3
	#define KETA_4 4 //4ケタごとに出現する[keta_4_moji]から総桁数を求める
	#define KETA_0 1 //[keta_4_moji]の要素番号の最大値を取得するため
    #define nine_trade 2 // kanji_num 文字列中の九まで置換

	std::string keta_4_moji[] = {"","万","億","兆","京","垓"};
	std::string keta_moji[] = {"十","百","千"};
	std::string kanji_num[] = {"一","二","三","四","五","六","七","八","九",""};

	// 配列結合関数を作成する
	std::string target_moji[] = {"一","二","三","四","五","六","七","八","九","十","百","千","万","億","兆","京","垓"};

    // 文字列の右側に「digit_0_assist」を付ける
	for (int i = 0; i <= (sizeof(target_moji) / sizeof(target_moji[0]) - KETA_0); i++) {
		moji = all_Replace(moji, target_moji[i], target_moji[i] + "digit_" + std::to_string(0) + "_assist");
	}

    // 文字列の左側の「digit_0_assist」を消す
	for (int i = 0; i <= (sizeof(target_moji) / sizeof(target_moji[0]) - 1); i++) {
		moji = all_Replace(moji, "digit_" + std::to_string(0) + "_assist" + target_moji[i], target_moji[i]);
	}

	for (int i = 0; i < ( (sizeof(keta_4_moji) / sizeof(keta_4_moji[0]) - KETA_0 ) * KETA_4 + keta_moji_ARRAY_SIZE); i++) {
		for (int j = i; j >= 0; j--) {
			for (int k = 0; k < (sizeof(kanji_num) / sizeof(kanji_num[0])); k++) {

				std::string before_trade;
				std::string after_trade;

				if ((i % KETA_4) == 0) {
					before_trade = kanji_num[k] + keta_4_moji[i / KETA_4] + ("digit_" + std::to_string(j) + "_assist");
					after_trade = ("digit_" + std::to_string(i + 1) + "_assist") + std::to_string((k + 1) % 10) + std::string(i - j, '0');
				} else {
					before_trade = kanji_num[k] + keta_moji[(i % KETA_4) - 1] + ("digit_" + std::to_string(j) + "_assist");
					after_trade = ("digit_" + std::to_string(i + 1) + "_assist") + std::to_string((int)((k + 1) / 10) + ((k + 1) % 10)) + std::string(i - j, '0');
				}	

				moji = all_Replace(moji, before_trade, after_trade);
			}
		}
	}
    
// 行政文書、法律文書なら下記２つともコメントアウト
#if (0) // 単純置換　郵便番号用
    for (int i = 0; i < (sizeof(kanji_num) / sizeof(kanji_num[0])); i++) {
        moji = all_Replace(moji, kanji_num[i], std::to_string(i + 1));
    }
    moji = all_Replace(moji,  "○" , std::to_string(0));
#endif

#if (1) // 一般文書用　一文字なら置換しない
    for (int i = 0; i < (sizeof(kanji_num) / sizeof(kanji_num[0])); i++) {
        moji = all_Replace(moji, "digit_1_assist" + std::to_string(i + 1), kanji_num[i]);
    }

    for (int i = 0; i < (sizeof(keta_moji) / sizeof(keta_moji[0])); i++) {
        moji = all_Replace(moji, ("digit_" + std::to_string(i + 2) + "_assist") + std::to_string(1) + std::string(i + 1, '0'), keta_moji[i]);
    }

    for (int i = 0; i < (sizeof(keta_4_moji) / sizeof(keta_4_moji[0])); i++) {
        moji = all_Replace(moji, ("digit_" + std::to_string(i * 4 + 1) + "_assist") + std::string(i * 4 + 1, '0'), keta_4_moji[i]);
    }
#endif

    // 50枚など算用数字の方が見やすい場合
    std::string unit_moji[] = {"個","人","枚","回","通"};
    for (int i = 0; i < (sizeof(unit_moji) / sizeof(unit_moji[0])); i++) {
        for (int j = 0; j < (sizeof(kanji_num) / sizeof(kanji_num[0])) - nine_trade; j++) {
            moji = all_Replace(moji, kanji_num[j] + unit_moji[i], std::to_string((j + 1)) + unit_moji[i]);            // 未完成
        }
    }

    //  アシスト文字を消去する
    for (int i = 0; i < ( (sizeof(keta_4_moji) / sizeof(keta_4_moji[0]) - KETA_0 ) * KETA_4 + keta_moji_ARRAY_SIZE) + 1; i++) {
        moji = all_Replace(moji,  ("digit_" + std::to_string(i + 1) + "_assist") , "");
    }

    moji = irregular(moji); //例外処理
    moji = legal_doc(moji); //法律文書用

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

std::string legal_doc(std::string std2) // 行政文書、法律文書用
{
    std2 = all_Replace(std2, "1部", "一部");
    std2 = all_Replace(std2, "1種", "一種");
    std2 = all_Replace(std2, "1人", "一人");
    std2 = all_Replace(std2, "1時", "一時");
    std2 = all_Replace(std2, "1般", "一般");
    std2 = all_Replace(std2, "1致", "一致");
    std2 = all_Replace(std2, "1身", "一身");
    std2 = all_Replace(std2, "1定", "一定");
    std2 = all_Replace(std2, "1切", "一切");
    std2 = all_Replace(std2, "同1", "同一");
    std2 = all_Replace(std2, "1の地方", "一の地方");
    std2 = all_Replace(std2, "10分", "十分");
    std2 = all_Replace(std2, "2重", "二重");
    std2 = all_Replace(std2, "第3者", "第三者");
    std2 = all_Replace(std2, "第3取得者", "第三取得者");

    return std2;
}

std::string irregular(std::string std3) //例外処理  (漢字でなければならない文字)
{
    std3 = all_Replace(std3, "十中八九", "十中八九");
    std3 = all_Replace(std3, "十二単衣", "十二単衣");
    std3 = all_Replace(std3, "五十嵐", "五十嵐");
    std3 = all_Replace(std3, "四十肩", "四十肩");
    //・・・・・・必要に応じて追加

    return std3;
}
