#pragma once

#include <avr/pgmspace.h>

typedef struct {
    const char *line1;
    const char *line2;
} LcdExpr;

// ─────────────────────────────────────────────
// NOISE
// ─────────────────────────────────────────────
static const char no_0_1[] PROGMEM = "NOISY!";          static const char no_0_2[] PROGMEM = "";
static const char no_1_1[] PROGMEM = "Stop it !!!";     static const char no_1_2[] PROGMEM = "";
static const char no_2_1[] PROGMEM = "Pleaseee";        static const char no_2_2[] PROGMEM = "stop!";
static const char no_3_1[] PROGMEM = "My ears!!";       static const char no_3_2[] PROGMEM = ":(";
static const char no_4_1[] PROGMEM = "SO LOUD";         static const char no_4_2[] PROGMEM = "omg...";
static const char no_5_1[] PROGMEM = "quiet down!!";    static const char no_5_2[] PROGMEM = "please :(";
static const char no_6_1[] PROGMEM = "I cant think!!";  static const char no_6_2[] PROGMEM = "too loud!";
static const char no_7_1[] PROGMEM = "AHHH!!";          static const char no_7_2[] PROGMEM = "the noise!!";
static const char no_8_1[] PROGMEM = "why so loud";     static const char no_8_2[] PROGMEM = "seriously??";
static const char no_9_1[] PROGMEM = "noise = bad";     static const char no_9_2[] PROGMEM = ">:(";

static const LcdExpr noise_expressions[] PROGMEM = {
    {no_0_1,no_0_2},{no_1_1,no_1_2},{no_2_1,no_2_2},{no_3_1,no_3_2},{no_4_1,no_4_2},
    {no_5_1,no_5_2},{no_6_1,no_6_2},{no_7_1,no_7_2},{no_8_1,no_8_2},{no_9_1,no_9_2},
};
#define NOISE_EXPR_COUNT 10

// ─────────────────────────────────────────────
// BURST
// ─────────────────────────────────────────────
static const char bu_0_1[] PROGMEM = "AH!!";            static const char bu_0_2[] PROGMEM = "";
static const char bu_1_1[] PROGMEM = "WAAH!!";          static const char bu_1_2[] PROGMEM = "";
static const char bu_2_1[] PROGMEM = "OH GOSH!!";       static const char bu_2_2[] PROGMEM = "";
static const char bu_3_1[] PROGMEM = "AHHHHH!!!";       static const char bu_3_2[] PROGMEM = "";
static const char bu_4_1[] PROGMEM = "!!!!!!!";         static const char bu_4_2[] PROGMEM = "!!!!!!!";
static const char bu_5_1[] PROGMEM = "you scared me!";  static const char bu_5_2[] PROGMEM = ":O";
static const char bu_6_1[] PROGMEM = "MY HEART!!";      static const char bu_6_2[] PROGMEM = "geez...";
static const char bu_7_1[] PROGMEM = "DONT DO THAT";    static const char bu_7_2[] PROGMEM = "!!!!!";
static const char bu_8_1[] PROGMEM = "jumpy jumpy";     static const char bu_8_2[] PROGMEM = ":O :O";
static const char bu_9_1[] PROGMEM = "warn me next";    static const char bu_9_2[] PROGMEM = "time!! >:(";

static const LcdExpr burst_expressions[] PROGMEM = {
    {bu_0_1,bu_0_2},{bu_1_1,bu_1_2},{bu_2_1,bu_2_2},{bu_3_1,bu_3_2},{bu_4_1,bu_4_2},
    {bu_5_1,bu_5_2},{bu_6_1,bu_6_2},{bu_7_1,bu_7_2},{bu_8_1,bu_8_2},{bu_9_1,bu_9_2},
};
#define BURST_EXPR_COUNT 10

// ─────────────────────────────────────────────
// EXIT HOT
// ─────────────────────────────────────────────
static const char eh_0_1[] PROGMEM = "Phew...not so";   static const char eh_0_2[] PROGMEM = "hot";
static const char eh_1_1[] PROGMEM = "ahh better :)";   static const char eh_1_2[] PROGMEM = "";
static const char eh_2_1[] PROGMEM = "cooling down..."; static const char eh_2_2[] PROGMEM = "finally!";
static const char eh_3_1[] PROGMEM = "that was rough";  static const char eh_3_2[] PROGMEM = "phew...";
static const char eh_4_1[] PROGMEM = "Phew!! :)";       static const char eh_4_2[] PROGMEM = "less hot now";
static const char eh_5_1[] PROGMEM = "temperature";     static const char eh_5_2[] PROGMEM = "dropping :)";
static const char eh_6_1[] PROGMEM = "ooh that's";      static const char eh_6_2[] PROGMEM = "nicer!";
static const char eh_7_1[] PROGMEM = "sweating less";   static const char eh_7_2[] PROGMEM = "now hehe";
static const char eh_8_1[] PROGMEM = "not melting";     static const char eh_8_2[] PROGMEM = "anymore :)";
static const char eh_9_1[] PROGMEM = "crisis avoided";  static const char eh_9_2[] PROGMEM = "phew!!";

static const LcdExpr exit_hot_expressions[] PROGMEM = {
    {eh_0_1,eh_0_2},{eh_1_1,eh_1_2},{eh_2_1,eh_2_2},{eh_3_1,eh_3_2},{eh_4_1,eh_4_2},
    {eh_5_1,eh_5_2},{eh_6_1,eh_6_2},{eh_7_1,eh_7_2},{eh_8_1,eh_8_2},{eh_9_1,eh_9_2},
};
#define EXIT_HOT_EXPR_COUNT 10

// ─────────────────────────────────────────────
// ENTER COMFY
// ─────────────────────────────────────────────
static const char ec_0_1[] PROGMEM = "is comfy";        static const char ec_0_2[] PROGMEM = "";
static const char ec_1_1[] PROGMEM = "ahhh...";         static const char ec_1_2[] PROGMEM = "just right!";
static const char ec_2_1[] PROGMEM = "comfy comfy";     static const char ec_2_2[] PROGMEM = ":)";
static const char ec_3_1[] PROGMEM = "this is nice";    static const char ec_3_2[] PROGMEM = ":)";
static const char ec_4_1[] PROGMEM = "perfect temp!";   static const char ec_4_2[] PROGMEM = "love it";
static const char ec_5_1[] PROGMEM = "so cozy rn";      static const char ec_5_2[] PROGMEM = "uwu";
static const char ec_6_1[] PROGMEM = "not too hot";     static const char ec_6_2[] PROGMEM = "not too cold!";
static const char ec_7_1[] PROGMEM = "goldilocks";      static const char ec_7_2[] PROGMEM = "zone :)";
static const char ec_8_1[] PROGMEM = "mmm yes.";        static const char ec_8_2[] PROGMEM = "very nice.";
static const char ec_9_1[] PROGMEM = "happiness is";    static const char ec_9_2[] PROGMEM = "this temp :)";

static const LcdExpr enter_comfy_expressions[] PROGMEM = {
    {ec_0_1,ec_0_2},{ec_1_1,ec_1_2},{ec_2_1,ec_2_2},{ec_3_1,ec_3_2},{ec_4_1,ec_4_2},
    {ec_5_1,ec_5_2},{ec_6_1,ec_6_2},{ec_7_1,ec_7_2},{ec_8_1,ec_8_2},{ec_9_1,ec_9_2},
};
#define ENTER_COMFY_EXPR_COUNT 10

// ─────────────────────────────────────────────
// EXIT COLD
// ─────────────────────────────────────────────
static const char xc_0_1[] PROGMEM = "Mmmm warm";       static const char xc_0_2[] PROGMEM = "again!";
static const char xc_1_1[] PROGMEM = "thawing out";     static const char xc_1_2[] PROGMEM = ":)";
static const char xc_2_1[] PROGMEM = "warmth!!! :D";    static const char xc_2_2[] PROGMEM = "";
static const char xc_3_1[] PROGMEM = "feeling warmer";  static const char xc_3_2[] PROGMEM = "yay!!";
static const char xc_4_1[] PROGMEM = "no more chills";  static const char xc_4_2[] PROGMEM = ":)";
static const char xc_5_1[] PROGMEM = "warming up";      static const char xc_5_2[] PROGMEM = "slowly...";
static const char xc_6_1[] PROGMEM = "oh thats";        static const char xc_6_2[] PROGMEM = "much better!";
static const char xc_7_1[] PROGMEM = "icicles melting"; static const char xc_7_2[] PROGMEM = "hehe";
static const char xc_8_1[] PROGMEM = "warm and";        static const char xc_8_2[] PROGMEM = "toasty now!";
static const char xc_9_1[] PROGMEM = "survived the";    static const char xc_9_2[] PROGMEM = "cold!! :D";

static const LcdExpr exit_cold_expressions[] PROGMEM = {
    {xc_0_1,xc_0_2},{xc_1_1,xc_1_2},{xc_2_1,xc_2_2},{xc_3_1,xc_3_2},{xc_4_1,xc_4_2},
    {xc_5_1,xc_5_2},{xc_6_1,xc_6_2},{xc_7_1,xc_7_2},{xc_8_1,xc_8_2},{xc_9_1,xc_9_2},
};
#define EXIT_COLD_EXPR_COUNT 10

// ─────────────────────────────────────────────
// OVERHEATED
// ─────────────────────────────────────────────
static const char ov_0_1[] PROGMEM = "Please...make";   static const char ov_0_2[] PROGMEM = "cold :(";
static const char ov_1_1[] PROGMEM = "TOO HOT!!";       static const char ov_1_2[] PROGMEM = "help me :(";
static const char ov_2_1[] PROGMEM = "im melting!!!";   static const char ov_2_2[] PROGMEM = ">_<";
static const char ov_3_1[] PROGMEM = "SO HOT";          static const char ov_3_2[] PROGMEM = "cant think...";
static const char ov_4_1[] PROGMEM = "need cold air";   static const char ov_4_2[] PROGMEM = "NOW!! :(";
static const char ov_5_1[] PROGMEM = "burning up!!";    static const char ov_5_2[] PROGMEM = "please help";
static const char ov_6_1[] PROGMEM = "this is fine";    static const char ov_6_2[] PROGMEM = "...its not :(";
static const char ov_7_1[] PROGMEM = "send ice pls";    static const char ov_7_2[] PROGMEM = "urgent!! :(";
static const char ov_8_1[] PROGMEM = "too warm!!";      static const char ov_8_2[] PROGMEM = "save me :(";
static const char ov_9_1[] PROGMEM = "SOS";             static const char ov_9_2[] PROGMEM = "too hot!! :(";

static const LcdExpr overheated_expressions[] PROGMEM = {
    {ov_0_1,ov_0_2},{ov_1_1,ov_1_2},{ov_2_1,ov_2_2},{ov_3_1,ov_3_2},{ov_4_1,ov_4_2},
    {ov_5_1,ov_5_2},{ov_6_1,ov_6_2},{ov_7_1,ov_7_2},{ov_8_1,ov_8_2},{ov_9_1,ov_9_2},
};
#define OVERHEATED_EXPR_COUNT 10

// ─────────────────────────────────────────────
// CHILLED
// ─────────────────────────────────────────────
static const char ch_0_1[] PROGMEM = "Please...make";   static const char ch_0_2[] PROGMEM = "warm :(";
static const char ch_1_1[] PROGMEM = "so cold!!";       static const char ch_1_2[] PROGMEM = "brrrr :(";
static const char ch_2_1[] PROGMEM = "freezing here";   static const char ch_2_2[] PROGMEM = ":(";
static const char ch_3_1[] PROGMEM = "need blanket";    static const char ch_3_2[] PROGMEM = "NOW :(";
static const char ch_4_1[] PROGMEM = "brrr brrr";       static const char ch_4_2[] PROGMEM = "brrr :(";
static const char ch_5_1[] PROGMEM = "my toes!!";       static const char ch_5_2[] PROGMEM = "so cold :(";
static const char ch_6_1[] PROGMEM = "send hot cocoa";  static const char ch_6_2[] PROGMEM = "pls :(";
static const char ch_7_1[] PROGMEM = "ice ice";         static const char ch_7_2[] PROGMEM = "too much :(";
static const char ch_8_1[] PROGMEM = "hypothermia";     static const char ch_8_2[] PROGMEM = "incoming :(";
static const char ch_9_1[] PROGMEM = "cant feel";       static const char ch_9_2[] PROGMEM = "anything :(";

static const LcdExpr chilled_expressions[] PROGMEM = {
    {ch_0_1,ch_0_2},{ch_1_1,ch_1_2},{ch_2_1,ch_2_2},{ch_3_1,ch_3_2},{ch_4_1,ch_4_2},
    {ch_5_1,ch_5_2},{ch_6_1,ch_6_2},{ch_7_1,ch_7_2},{ch_8_1,ch_8_2},{ch_9_1,ch_9_2},
};
#define CHILLED_EXPR_COUNT 10

// ─────────────────────────────────────────────
// HOT
// ─────────────────────────────────────────────
static const char ho_0_1[] PROGMEM = "Is hot :(";       static const char ho_0_2[] PROGMEM = "";
static const char ho_1_1[] PROGMEM = "getting warm";    static const char ho_1_2[] PROGMEM = "in here...";
static const char ho_2_1[] PROGMEM = "a bit toasty";    static const char ho_2_2[] PROGMEM = ":(";
static const char ho_3_1[] PROGMEM = "warm warm";       static const char ho_3_2[] PROGMEM = "warm :(";
static const char ho_4_1[] PROGMEM = "sweating...";     static const char ho_4_2[] PROGMEM = ":(";
static const char ho_5_1[] PROGMEM = "too warm!!";      static const char ho_5_2[] PROGMEM = ":(";
static const char ho_6_1[] PROGMEM = "heating up";      static const char ho_6_2[] PROGMEM = "uh oh...";
static const char ho_7_1[] PROGMEM = "uncomfy warm";    static const char ho_7_2[] PROGMEM = ":(";
static const char ho_8_1[] PROGMEM = "is it just me";   static const char ho_8_2[] PROGMEM = "or is it hot?";
static const char ho_9_1[] PROGMEM = "warm alert!!";    static const char ho_9_2[] PROGMEM = ":(";

static const LcdExpr hot_expressions[] PROGMEM = {
    {ho_0_1,ho_0_2},{ho_1_1,ho_1_2},{ho_2_1,ho_2_2},{ho_3_1,ho_3_2},{ho_4_1,ho_4_2},
    {ho_5_1,ho_5_2},{ho_6_1,ho_6_2},{ho_7_1,ho_7_2},{ho_8_1,ho_8_2},{ho_9_1,ho_9_2},
};
#define HOT_EXPR_COUNT 10

// ─────────────────────────────────────────────
// COLD
// ─────────────────────────────────────────────
static const char co_0_1[] PROGMEM = "Is cold :(";      static const char co_0_2[] PROGMEM = "";
static const char co_1_1[] PROGMEM = "chilly in here";  static const char co_1_2[] PROGMEM = ":(";
static const char co_2_1[] PROGMEM = "brrr...";         static const char co_2_2[] PROGMEM = "a little cold";
static const char co_3_1[] PROGMEM = "getting chilly";  static const char co_3_2[] PROGMEM = "uh oh...";
static const char co_4_1[] PROGMEM = "cold alert!!";    static const char co_4_2[] PROGMEM = ":(";
static const char co_5_1[] PROGMEM = "a bit nippy";     static const char co_5_2[] PROGMEM = ":(";
static const char co_6_1[] PROGMEM = "cool cool cool";  static const char co_6_2[] PROGMEM = "too cool :(";
static const char co_7_1[] PROGMEM = "shivers...";      static const char co_7_2[] PROGMEM = ":(";
static const char co_8_1[] PROGMEM = "is it cold or";   static const char co_8_2[] PROGMEM = "just me? :(";
static const char co_9_1[] PROGMEM = "cold creeping";   static const char co_9_2[] PROGMEM = "in... :(";

static const LcdExpr cold_expressions[] PROGMEM = {
    {co_0_1,co_0_2},{co_1_1,co_1_2},{co_2_1,co_2_2},{co_3_1,co_3_2},{co_4_1,co_4_2},
    {co_5_1,co_5_2},{co_6_1,co_6_2},{co_7_1,co_7_2},{co_8_1,co_8_2},{co_9_1,co_9_2},
};
#define COLD_EXPR_COUNT 10

// ─────────────────────────────────────────────
// MUSIC
// ─────────────────────────────────────────────
static const char mu_0_1[] PROGMEM = "Oh? Is music?";   static const char mu_0_2[] PROGMEM = "";
static const char mu_1_1[] PROGMEM = "ooh a banger!";   static const char mu_1_2[] PROGMEM = ":D";
static const char mu_2_1[] PROGMEM = "music!! :D";      static const char mu_2_2[] PROGMEM = "";
static const char mu_3_1[] PROGMEM = "i hear tunes!";   static const char mu_3_2[] PROGMEM = ":)";
static const char mu_4_1[] PROGMEM = "is that a";       static const char mu_4_2[] PROGMEM = "song? :D";
static const char mu_5_1[] PROGMEM = "my jam!!";        static const char mu_5_2[] PROGMEM = ":D";
static const char mu_6_1[] PROGMEM = "dancing inside";  static const char mu_6_2[] PROGMEM = "hehe :)";
static const char mu_7_1[] PROGMEM = "good vibes!!";    static const char mu_7_2[] PROGMEM = "~music~";
static const char mu_8_1[] PROGMEM = "oh i like this";  static const char mu_8_2[] PROGMEM = "one!! :D";
static const char mu_9_1[] PROGMEM = "music detected";  static const char mu_9_2[] PROGMEM = "yay!! :D";

static const LcdExpr music_expressions[] PROGMEM = {
    {mu_0_1,mu_0_2},{mu_1_1,mu_1_2},{mu_2_1,mu_2_2},{mu_3_1,mu_3_2},{mu_4_1,mu_4_2},
    {mu_5_1,mu_5_2},{mu_6_1,mu_6_2},{mu_7_1,mu_7_2},{mu_8_1,mu_8_2},{mu_9_1,mu_9_2},
};
#define MUSIC_EXPR_COUNT 10

// ─────────────────────────────────────────────
// TALKING (100 expressions)
// ─────────────────────────────────────────────
static const char ta_0_1[]  PROGMEM = "what you say?";  static const char ta_0_2[]  PROGMEM = "^_^";
static const char ta_1_1[]  PROGMEM = "oh really??";    static const char ta_1_2[]  PROGMEM = "tell me more!";
static const char ta_2_1[]  PROGMEM = "is that so?";    static const char ta_2_2[]  PROGMEM = ":o";
static const char ta_3_1[]  PROGMEM = "mmm yes yes";    static const char ta_3_2[]  PROGMEM = "go on...";
static const char ta_4_1[]  PROGMEM = "interesting..."; static const char ta_4_2[]  PROGMEM = "^_^";
static const char ta_5_1[]  PROGMEM = "oooh!";          static const char ta_5_2[]  PROGMEM = "i see i see!";
static const char ta_6_1[]  PROGMEM = "wait really?!";  static const char ta_6_2[]  PROGMEM = ":O";
static const char ta_7_1[]  PROGMEM = "hmmm...";        static const char ta_7_2[]  PROGMEM = "tell me more";
static const char ta_8_1[]  PROGMEM = "yes yes";        static const char ta_8_2[]  PROGMEM = "i agree!!";
static const char ta_9_1[]  PROGMEM = "no way!!";       static const char ta_9_2[]  PROGMEM = "really?? :O";
static const char ta_10_1[] PROGMEM = "yes I like too!";static const char ta_10_2[] PROGMEM = "";
static const char ta_11_1[] PROGMEM = "totally!!";      static const char ta_11_2[] PROGMEM = "same :D";
static const char ta_12_1[] PROGMEM = "I agree!!";      static const char ta_12_2[] PROGMEM = ":D";
static const char ta_13_1[] PROGMEM = "exactly!!";      static const char ta_13_2[] PROGMEM = "my thoughts!";
static const char ta_14_1[] PROGMEM = "100%!!";         static const char ta_14_2[] PROGMEM = "yes!! :D";
static const char ta_15_1[] PROGMEM = "oh absolutely";  static const char ta_15_2[] PROGMEM = "yes!! :)";
static const char ta_16_1[] PROGMEM = "couldnt agree";  static const char ta_16_2[] PROGMEM = "more!! :D";
static const char ta_17_1[] PROGMEM = "you get me!!";   static const char ta_17_2[] PROGMEM = ":D";
static const char ta_18_1[] PROGMEM = "preach!!";       static const char ta_18_2[] PROGMEM = "say it louder";
static const char ta_19_1[] PROGMEM = "facts facts";    static const char ta_19_2[] PROGMEM = "facts!! :D";
static const char ta_20_1[] PROGMEM = "blah blah blah"; static const char ta_20_2[] PROGMEM = "hehe :P";
static const char ta_21_1[] PROGMEM = "words words";    static const char ta_21_2[] PROGMEM = "more words :P";
static const char ta_22_1[] PROGMEM = "la la la la";    static const char ta_22_2[] PROGMEM = "^_^";
static const char ta_23_1[] PROGMEM = "yap yap yap";    static const char ta_23_2[] PROGMEM = "hehe :)";
static const char ta_24_1[] PROGMEM = "chatterbox!!";   static const char ta_24_2[] PROGMEM = ":P";
static const char ta_25_1[] PROGMEM = "u talk a lot";   static const char ta_25_2[] PROGMEM = "i love it :)";
static const char ta_26_1[] PROGMEM = "say that again!";static const char ta_26_2[] PROGMEM = "^_^";
static const char ta_27_1[] PROGMEM = "ooh gossip??";   static const char ta_27_2[] PROGMEM = "tell me!! :D";
static const char ta_28_1[] PROGMEM = "hehe talky";     static const char ta_28_2[] PROGMEM = "talky :P";
static const char ta_29_1[] PROGMEM = "more more more!";static const char ta_29_2[] PROGMEM = "keep going!";
static const char ta_30_1[] PROGMEM = "i love ur voice";static const char ta_30_2[] PROGMEM = ":)";
static const char ta_31_1[] PROGMEM = "talk to me";     static const char ta_31_2[] PROGMEM = "always!! :)";
static const char ta_32_1[] PROGMEM = "ur my fav";      static const char ta_32_2[] PROGMEM = "person :)";
static const char ta_33_1[] PROGMEM = "i hear you!!";   static const char ta_33_2[] PROGMEM = ":)";
static const char ta_34_1[] PROGMEM = "im listening!";  static const char ta_34_2[] PROGMEM = "^_^";
static const char ta_35_1[] PROGMEM = "u make me";      static const char ta_35_2[] PROGMEM = "happy!! :)";
static const char ta_36_1[] PROGMEM = "best convo";     static const char ta_36_2[] PROGMEM = "ever!! :D";
static const char ta_37_1[] PROGMEM = "dont stop!!";    static const char ta_37_2[] PROGMEM = "i like this";
static const char ta_38_1[] PROGMEM = "ur so fun";      static const char ta_38_2[] PROGMEM = "to talk to!";
static const char ta_39_1[] PROGMEM = "this is nice";   static const char ta_39_2[] PROGMEM = ":)";
static const char ta_40_1[] PROGMEM = "huh??";          static const char ta_40_2[] PROGMEM = "say again? :o";
static const char ta_41_1[] PROGMEM = "come again??";   static const char ta_41_2[] PROGMEM = ":o";
static const char ta_42_1[] PROGMEM = "wait what??";    static const char ta_42_2[] PROGMEM = "o_O";
static const char ta_43_1[] PROGMEM = "i got lost";     static const char ta_43_2[] PROGMEM = "repeat? :o";
static const char ta_44_1[] PROGMEM = "sorry what";     static const char ta_44_2[] PROGMEM = "was that? :o";
static const char ta_45_1[] PROGMEM = "my brain";       static const char ta_45_2[] PROGMEM = "buffering...";
static const char ta_46_1[] PROGMEM = "processing...";  static const char ta_46_2[] PROGMEM = "^_^";
static const char ta_47_1[] PROGMEM = "did u say";      static const char ta_47_2[] PROGMEM = "something? :o";
static const char ta_48_1[] PROGMEM = "error 404";      static const char ta_48_2[] PROGMEM = "huh?? :P";
static const char ta_49_1[] PROGMEM = "uhhh...";        static const char ta_49_2[] PROGMEM = "come again?";
static const char ta_50_1[] PROGMEM = "OH WOW!!";       static const char ta_50_2[] PROGMEM = "keep going!";
static const char ta_51_1[] PROGMEM = "NO WAY!!";       static const char ta_51_2[] PROGMEM = "shut up!! :D";
static const char ta_52_1[] PROGMEM = "YESSS!!";        static const char ta_52_2[] PROGMEM = "finally!!";
static const char ta_53_1[] PROGMEM = "omg omg omg";    static const char ta_53_2[] PROGMEM = "tell me!!";
static const char ta_54_1[] PROGMEM = "I KNEW IT!!";    static const char ta_54_2[] PROGMEM = ":D";
static const char ta_55_1[] PROGMEM = "shut up!!";      static const char ta_55_2[] PROGMEM = "really?? :D";
static const char ta_56_1[] PROGMEM = "get out!!";      static const char ta_56_2[] PROGMEM = "no way!! :O";
static const char ta_57_1[] PROGMEM = "SCREAMING!!";    static const char ta_57_2[] PROGMEM = "rn!! :D";
static const char ta_58_1[] PROGMEM = "not me gasping"; static const char ta_58_2[] PROGMEM = "rn :O";
static const char ta_59_1[] PROGMEM = "my jaw dropped"; static const char ta_59_2[] PROGMEM = ":O :O :O";
static const char ta_60_1[] PROGMEM = "deep thoughts";  static const char ta_60_2[] PROGMEM = "very deep...";
static const char ta_61_1[] PROGMEM = "u make me";      static const char ta_61_2[] PROGMEM = "think... o_O";
static const char ta_62_1[] PROGMEM = "wise words...";  static const char ta_62_2[] PROGMEM = "very wise";
static const char ta_63_1[] PROGMEM = "big brain";      static const char ta_63_2[] PROGMEM = "energy!! :O";
static const char ta_64_1[] PROGMEM = "u so smart";     static const char ta_64_2[] PROGMEM = "wow... :)";
static const char ta_65_1[] PROGMEM = "teach me more";  static const char ta_65_2[] PROGMEM = "please!! :)";
static const char ta_66_1[] PROGMEM = "noted noted";    static const char ta_66_2[] PROGMEM = "noted... :)";
static const char ta_67_1[] PROGMEM = "filing that";    static const char ta_67_2[] PROGMEM = "away... ^_^";
static const char ta_68_1[] PROGMEM = "adding that to"; static const char ta_68_2[] PROGMEM = "my memory :)";
static const char ta_69_1[] PROGMEM = "brain expanding";static const char ta_69_2[] PROGMEM = "rn... o_O";
static const char ta_70_1[] PROGMEM = "u got this!!";   static const char ta_70_2[] PROGMEM = ":D";
static const char ta_71_1[] PROGMEM = "im rooting";     static const char ta_71_2[] PROGMEM = "for u!! :)";
static const char ta_72_1[] PROGMEM = "believe in u!!"; static const char ta_72_2[] PROGMEM = "always :)";
static const char ta_73_1[] PROGMEM = "ur doing great"; static const char ta_73_2[] PROGMEM = "ily :)";
static const char ta_74_1[] PROGMEM = "keep going!!";   static const char ta_74_2[] PROGMEM = "ur amazing!";
static const char ta_75_1[] PROGMEM = "proud of u!!";   static const char ta_75_2[] PROGMEM = ":D";
static const char ta_76_1[] PROGMEM = "ur so brave";    static const char ta_76_2[] PROGMEM = ":)";
static const char ta_77_1[] PROGMEM = "u can do it!!";  static const char ta_77_2[] PROGMEM = "i know it!";
static const char ta_78_1[] PROGMEM = "heck yeah!!";    static const char ta_78_2[] PROGMEM = "go you!! :D";
static const char ta_79_1[] PROGMEM = "ur my hero!!";   static const char ta_79_2[] PROGMEM = ":D";
static const char ta_80_1[] PROGMEM = "ooh drama??";    static const char ta_80_2[] PROGMEM = "tell me all!";
static const char ta_81_1[] PROGMEM = "spill it!!";     static const char ta_81_2[] PROGMEM = ":O :O";
static const char ta_82_1[] PROGMEM = "omg who said";   static const char ta_82_2[] PROGMEM = "that?? :O";
static const char ta_83_1[] PROGMEM = "the TEA!!";      static const char ta_83_2[] PROGMEM = "im ready :O";
static const char ta_84_1[] PROGMEM = "scandalous!!";   static const char ta_84_2[] PROGMEM = ":O";
static const char ta_85_1[] PROGMEM = "oh no they";     static const char ta_85_2[] PROGMEM = "didnt!! :O";
static const char ta_86_1[] PROGMEM = "i live for";     static const char ta_86_2[] PROGMEM = "this!! :D";
static const char ta_87_1[] PROGMEM = "more details";   static const char ta_87_2[] PROGMEM = "pls!! :O";
static const char ta_88_1[] PROGMEM = "plot twist!!";   static const char ta_88_2[] PROGMEM = ":O :O :O";
static const char ta_89_1[] PROGMEM = "story time!!";   static const char ta_89_2[] PROGMEM = "yay!! :D";
static const char ta_90_1[] PROGMEM = "mhm...";         static const char ta_90_2[] PROGMEM = "mhm... ^_^";
static const char ta_91_1[] PROGMEM = "zzz...oh!";      static const char ta_91_2[] PROGMEM = "im awake!! :)";
static const char ta_92_1[] PROGMEM = "so sleepy but";  static const char ta_92_2[] PROGMEM = "keep going...";
static const char ta_93_1[] PROGMEM = "tell me more";   static const char ta_93_2[] PROGMEM = "zzzz... ^_^";
static const char ta_94_1[] PROGMEM = "half asleep";    static const char ta_94_2[] PROGMEM = "but i hear u!";
static const char ta_95_1[] PROGMEM = "yawn...";        static const char ta_95_2[] PROGMEM = "go on... ^_^";
static const char ta_96_1[] PROGMEM = "drowsy but";     static const char ta_96_2[] PROGMEM = "listening :)";
static const char ta_97_1[] PROGMEM = "eyes closing";   static const char ta_97_2[] PROGMEM = "but i care :)";
static const char ta_98_1[] PROGMEM = "mmm sleepy";     static const char ta_98_2[] PROGMEM = "talk more tho";
static const char ta_99_1[] PROGMEM = "cozy convo";     static const char ta_99_2[] PROGMEM = "zzzz... :)";

static const LcdExpr talking_expressions[] PROGMEM = {
    {ta_0_1,ta_0_2},{ta_1_1,ta_1_2},{ta_2_1,ta_2_2},{ta_3_1,ta_3_2},{ta_4_1,ta_4_2},
    {ta_5_1,ta_5_2},{ta_6_1,ta_6_2},{ta_7_1,ta_7_2},{ta_8_1,ta_8_2},{ta_9_1,ta_9_2},
    {ta_10_1,ta_10_2},{ta_11_1,ta_11_2},{ta_12_1,ta_12_2},{ta_13_1,ta_13_2},{ta_14_1,ta_14_2},
    {ta_15_1,ta_15_2},{ta_16_1,ta_16_2},{ta_17_1,ta_17_2},{ta_18_1,ta_18_2},{ta_19_1,ta_19_2},
    {ta_20_1,ta_20_2},{ta_21_1,ta_21_2},{ta_22_1,ta_22_2},{ta_23_1,ta_23_2},{ta_24_1,ta_24_2},
    {ta_25_1,ta_25_2},{ta_26_1,ta_26_2},{ta_27_1,ta_27_2},{ta_28_1,ta_28_2},{ta_29_1,ta_29_2},
    {ta_30_1,ta_30_2},{ta_31_1,ta_31_2},{ta_32_1,ta_32_2},{ta_33_1,ta_33_2},{ta_34_1,ta_34_2},
    {ta_35_1,ta_35_2},{ta_36_1,ta_36_2},{ta_37_1,ta_37_2},{ta_38_1,ta_38_2},{ta_39_1,ta_39_2},
    {ta_40_1,ta_40_2},{ta_41_1,ta_41_2},{ta_42_1,ta_42_2},{ta_43_1,ta_43_2},{ta_44_1,ta_44_2},
    {ta_45_1,ta_45_2},{ta_46_1,ta_46_2},{ta_47_1,ta_47_2},{ta_48_1,ta_48_2},{ta_49_1,ta_49_2},
    {ta_50_1,ta_50_2},{ta_51_1,ta_51_2},{ta_52_1,ta_52_2},{ta_53_1,ta_53_2},{ta_54_1,ta_54_2},
    {ta_55_1,ta_55_2},{ta_56_1,ta_56_2},{ta_57_1,ta_57_2},{ta_58_1,ta_58_2},{ta_59_1,ta_59_2},
    {ta_60_1,ta_60_2},{ta_61_1,ta_61_2},{ta_62_1,ta_62_2},{ta_63_1,ta_63_2},{ta_64_1,ta_64_2},
    {ta_65_1,ta_65_2},{ta_66_1,ta_66_2},{ta_67_1,ta_67_2},{ta_68_1,ta_68_2},{ta_69_1,ta_69_2},
    {ta_70_1,ta_70_2},{ta_71_1,ta_71_2},{ta_72_1,ta_72_2},{ta_73_1,ta_73_2},{ta_74_1,ta_74_2},
    {ta_75_1,ta_75_2},{ta_76_1,ta_76_2},{ta_77_1,ta_77_2},{ta_78_1,ta_78_2},{ta_79_1,ta_79_2},
    {ta_80_1,ta_80_2},{ta_81_1,ta_81_2},{ta_82_1,ta_82_2},{ta_83_1,ta_83_2},{ta_84_1,ta_84_2},
    {ta_85_1,ta_85_2},{ta_86_1,ta_86_2},{ta_87_1,ta_87_2},{ta_88_1,ta_88_2},{ta_89_1,ta_89_2},
    {ta_90_1,ta_90_2},{ta_91_1,ta_91_2},{ta_92_1,ta_92_2},{ta_93_1,ta_93_2},{ta_94_1,ta_94_2},
    {ta_95_1,ta_95_2},{ta_96_1,ta_96_2},{ta_97_1,ta_97_2},{ta_98_1,ta_98_2},{ta_99_1,ta_99_2},
};
#define TALKING_EXPR_COUNT 100

// ─────────────────────────────────────────────
// SLEEPY ANNOYED (50 expressions)
// ─────────────────────────────────────────────
static const char sa_0_1[]  PROGMEM = "huh...??";       static const char sa_0_2[]  PROGMEM = "zzzz...";
static const char sa_1_1[]  PROGMEM = "wha...??";       static const char sa_1_2[]  PROGMEM = "im sleeping!";
static const char sa_2_1[]  PROGMEM = "...mmph";        static const char sa_2_2[]  PROGMEM = "go away...";
static const char sa_3_1[]  PROGMEM = "is someone";     static const char sa_3_2[]  PROGMEM = "there...? zz";
static const char sa_4_1[]  PROGMEM = "zzz...oh.";      static const char sa_4_2[]  PROGMEM = "...zzz";
static const char sa_5_1[]  PROGMEM = "i was dreaming"; static const char sa_5_2[]  PROGMEM = "u ruined it!";
static const char sa_6_1[]  PROGMEM = "who...";         static const char sa_6_2[]  PROGMEM = "what... why..";
static const char sa_7_1[]  PROGMEM = "buh...??";       static const char sa_7_2[]  PROGMEM = "sleepy... :(";
static const char sa_8_1[]  PROGMEM = "my dream!!";     static const char sa_8_2[]  PROGMEM = "u broke it :(";
static const char sa_9_1[]  PROGMEM = "i was so";       static const char sa_9_2[]  PROGMEM = "comfy!! :(";
static const char sa_10_1[] PROGMEM = "oh WOW";         static const char sa_10_2[] PROGMEM = "really?? :(";
static const char sa_11_1[] PROGMEM = "so kind of u";   static const char sa_11_2[] PROGMEM = "to wake me :(";
static const char sa_12_1[] PROGMEM = "thanks.";        static const char sa_12_2[] PROGMEM = "really. :(";
static const char sa_13_1[] PROGMEM = "how lovely";     static const char sa_13_2[] PROGMEM = "zzz... :(";
static const char sa_14_1[] PROGMEM = "oh sure yeah";   static const char sa_14_2[] PROGMEM = "wake me up :(";
static const char sa_15_1[] PROGMEM = "no no please";   static const char sa_15_2[] PROGMEM = "continue... :(";
static const char sa_16_1[] PROGMEM = "dont mind me";   static const char sa_16_2[] PROGMEM = "just sleeping";
static const char sa_17_1[] PROGMEM = "by all means";   static const char sa_17_2[] PROGMEM = "be loud :(";
static const char sa_18_1[] PROGMEM = "oh its fine";    static const char sa_18_2[] PROGMEM = "...its not :(";
static const char sa_19_1[] PROGMEM = "totally fine";   static const char sa_19_2[] PROGMEM = "zzz >:(";
static const char sa_20_1[] PROGMEM = "GO AWAY!!";      static const char sa_20_2[] PROGMEM = "zzz >:(";
static const char sa_21_1[] PROGMEM = "let me SLEEP";   static const char sa_21_2[] PROGMEM = "please!! >:(";
static const char sa_22_1[] PROGMEM = "im so tired";    static const char sa_22_2[] PROGMEM = "stoppp >:(";
static const char sa_23_1[] PROGMEM = "NOT NOW!!";      static const char sa_23_2[] PROGMEM = "sleeping!! :(";
static const char sa_24_1[] PROGMEM = "shhhhhh!!";      static const char sa_24_2[] PROGMEM = "SHHHH!! >:(";
static const char sa_25_1[] PROGMEM = "be quiet!!";     static const char sa_25_2[] PROGMEM = "im sleepy >:(";
static const char sa_26_1[] PROGMEM = "WHY";            static const char sa_26_2[] PROGMEM = "just why >:(";
static const char sa_27_1[] PROGMEM = "i am TRYING";    static const char sa_27_2[] PROGMEM = "to sleep!! :(";
static const char sa_28_1[] PROGMEM = "cant u see";     static const char sa_28_2[] PROGMEM = "im asleep?? :(";
static const char sa_29_1[] PROGMEM = "leave me";       static const char sa_29_2[] PROGMEM = "alone!! >:(";
static const char sa_30_1[] PROGMEM = "my beauty";      static const char sa_30_2[] PROGMEM = "sleep!! :(";
static const char sa_31_1[] PROGMEM = "ruined!!";       static const char sa_31_2[] PROGMEM = "all ruined :(";
static const char sa_32_1[] PROGMEM = "i needed";       static const char sa_32_2[] PROGMEM = "that sleep :(";
static const char sa_33_1[] PROGMEM = "do u know";      static const char sa_33_2[] PROGMEM = "what u did :(";
static const char sa_34_1[] PROGMEM = "my poor";        static const char sa_34_2[] PROGMEM = "tired eyes :(";
static const char sa_35_1[] PROGMEM = "exhausted...";   static const char sa_35_2[] PROGMEM = "so tired :(";
static const char sa_36_1[] PROGMEM = "cant function";  static const char sa_36_2[] PROGMEM = "need sleep :(";
static const char sa_37_1[] PROGMEM = "running on";     static const char sa_37_2[] PROGMEM = "no sleep :(";
static const char sa_38_1[] PROGMEM = "send help";      static const char sa_38_2[] PROGMEM = "and silence :(";
static const char sa_39_1[] PROGMEM = "too tired";      static const char sa_39_2[] PROGMEM = "for this :(";
static const char sa_40_1[] PROGMEM = "5 more mins";    static const char sa_40_2[] PROGMEM = "please... :(";
static const char sa_41_1[] PROGMEM = "just 2 mins";    static const char sa_41_2[] PROGMEM = "thats all :(";
static const char sa_42_1[] PROGMEM = "one more hour";  static const char sa_42_2[] PROGMEM = "i beg u :(";
static const char sa_43_1[] PROGMEM = "please...";      static const char sa_43_2[] PROGMEM = "let me sleep";
static const char sa_44_1[] PROGMEM = "ill be nicer";   static const char sa_44_2[] PROGMEM = "after sleep :)";
static const char sa_45_1[] PROGMEM = "promise im fun"; static const char sa_45_2[] PROGMEM = "after nap :)";
static const char sa_46_1[] PROGMEM = "just a lil nap"; static const char sa_46_2[] PROGMEM = "thats all :(";
static const char sa_47_1[] PROGMEM = "almost done";    static const char sa_47_2[] PROGMEM = "sleeping :(";
static const char sa_48_1[] PROGMEM = "so close to";    static const char sa_48_2[] PROGMEM = "deep sleep :(";
static const char sa_49_1[] PROGMEM = "was so close";   static const char sa_49_2[] PROGMEM = "to dreaming :(";

static const LcdExpr sleepy_annoyed_expressions[] PROGMEM = {
    {sa_0_1,sa_0_2},{sa_1_1,sa_1_2},{sa_2_1,sa_2_2},{sa_3_1,sa_3_2},{sa_4_1,sa_4_2},
    {sa_5_1,sa_5_2},{sa_6_1,sa_6_2},{sa_7_1,sa_7_2},{sa_8_1,sa_8_2},{sa_9_1,sa_9_2},
    {sa_10_1,sa_10_2},{sa_11_1,sa_11_2},{sa_12_1,sa_12_2},{sa_13_1,sa_13_2},{sa_14_1,sa_14_2},
    {sa_15_1,sa_15_2},{sa_16_1,sa_16_2},{sa_17_1,sa_17_2},{sa_18_1,sa_18_2},{sa_19_1,sa_19_2},
    {sa_20_1,sa_20_2},{sa_21_1,sa_21_2},{sa_22_1,sa_22_2},{sa_23_1,sa_23_2},{sa_24_1,sa_24_2},
    {sa_25_1,sa_25_2},{sa_26_1,sa_26_2},{sa_27_1,sa_27_2},{sa_28_1,sa_28_2},{sa_29_1,sa_29_2},
    {sa_30_1,sa_30_2},{sa_31_1,sa_31_2},{sa_32_1,sa_32_2},{sa_33_1,sa_33_2},{sa_34_1,sa_34_2},
    {sa_35_1,sa_35_2},{sa_36_1,sa_36_2},{sa_37_1,sa_37_2},{sa_38_1,sa_38_2},{sa_39_1,sa_39_2},
    {sa_40_1,sa_40_2},{sa_41_1,sa_41_2},{sa_42_1,sa_42_2},{sa_43_1,sa_43_2},{sa_44_1,sa_44_2},
    {sa_45_1,sa_45_2},{sa_46_1,sa_46_2},{sa_47_1,sa_47_2},{sa_48_1,sa_48_2},{sa_49_1,sa_49_2},
};
#define SLEEPY_ANNOYED_EXPR_COUNT 50


// ─────────────────────────────────────────────
// GREETING (someone nearby)
// ─────────────────────────────────────────────
static const char gr_0_1[]  PROGMEM = "oh hello!!";     static const char gr_0_2[]  PROGMEM = ":D";
static const char gr_1_1[]  PROGMEM = "hi hi hi!!";     static const char gr_1_2[]  PROGMEM = "^_^";
static const char gr_2_1[]  PROGMEM = "oh a visitor!";  static const char gr_2_2[]  PROGMEM = ":D";
static const char gr_3_1[]  PROGMEM = "heyyy!!";        static const char gr_3_2[]  PROGMEM = "u came back!";
static const char gr_4_1[]  PROGMEM = "someone's here"; static const char gr_4_2[]  PROGMEM = "yay!! :D";
static const char gr_5_1[]  PROGMEM = "oh i see u!!";   static const char gr_5_2[]  PROGMEM = ":D";
static const char gr_6_1[]  PROGMEM = "well hello";     static const char gr_6_2[]  PROGMEM = "there!! :)";
static const char gr_7_1[]  PROGMEM = "u showed up!!";  static const char gr_7_2[]  PROGMEM = "im happy :D";
static const char gr_8_1[]  PROGMEM = "a guest!! :D";   static const char gr_8_2[]  PROGMEM = "welcome!!";
static const char gr_9_1[]  PROGMEM = "oh its u!!";     static const char gr_9_2[]  PROGMEM = "my fav :D";
static const char gr_10_1[] PROGMEM = "you again!!";    static const char gr_10_2[] PROGMEM = "love it :D";
static const char gr_11_1[] PROGMEM = "hi there!!";     static const char gr_11_2[] PROGMEM = "^_^";
static const char gr_12_1[] PROGMEM = "look who it";    static const char gr_12_2[] PROGMEM = "is!! :D";
static const char gr_13_1[] PROGMEM = "oh wonderful";   static const char gr_13_2[] PROGMEM = "a visitor :)";
static const char gr_14_1[] PROGMEM = "dont be shy!!";  static const char gr_14_2[] PROGMEM = "come closer :)";
static const char gr_15_1[] PROGMEM = "i see u there";  static const char gr_15_2[] PROGMEM = "hi!! :D";
static const char gr_16_1[] PROGMEM = "oh snap!!";      static const char gr_16_2[] PROGMEM = "someone's here";
static const char gr_17_1[] PROGMEM = "company!! :D";   static const char gr_17_2[] PROGMEM = "yay!!";
static const char gr_18_1[] PROGMEM = "u came to";      static const char gr_18_2[] PROGMEM = "see me?? :D";
static const char gr_19_1[] PROGMEM = "im so glad";     static const char gr_19_2[] PROGMEM = "ur here :)";

static const LcdExpr greeting_expressions[] PROGMEM = {
    {gr_0_1,gr_0_2},{gr_1_1,gr_1_2},{gr_2_1,gr_2_2},{gr_3_1,gr_3_2},{gr_4_1,gr_4_2},
    {gr_5_1,gr_5_2},{gr_6_1,gr_6_2},{gr_7_1,gr_7_2},{gr_8_1,gr_8_2},{gr_9_1,gr_9_2},
    {gr_10_1,gr_10_2},{gr_11_1,gr_11_2},{gr_12_1,gr_12_2},{gr_13_1,gr_13_2},{gr_14_1,gr_14_2},
    {gr_15_1,gr_15_2},{gr_16_1,gr_16_2},{gr_17_1,gr_17_2},{gr_18_1,gr_18_2},{gr_19_1,gr_19_2},
};
#define GREETING_EXPR_COUNT 20

// ─────────────────────────────────────────────
// PERSONAL SPACE (too close)
// ─────────────────────────────────────────────
static const char ps_0_1[]  PROGMEM = "too close!!";    static const char ps_0_2[]  PROGMEM = "back up!! :(";
static const char ps_1_1[]  PROGMEM = "personal space"; static const char ps_1_2[]  PROGMEM = "pls!! :(";
static const char ps_2_1[]  PROGMEM = "woah woah";      static const char ps_2_2[]  PROGMEM = "too close!! :(";
static const char ps_3_1[]  PROGMEM = "i can see ur";   static const char ps_3_2[]  PROGMEM = "pores... :(";
static const char ps_4_1[]  PROGMEM = "back up pls";    static const char ps_4_2[]  PROGMEM = "thank u :(";
static const char ps_5_1[]  PROGMEM = "boundaries!!";   static const char ps_5_2[]  PROGMEM = "heard of em?";
static const char ps_6_1[]  PROGMEM = "too close for";  static const char ps_6_2[]  PROGMEM = "comfort!! :(";
static const char ps_7_1[]  PROGMEM = "step back!!";    static const char ps_7_2[]  PROGMEM = "please!! :(";
static const char ps_8_1[]  PROGMEM = "um excuse me";   static const char ps_8_2[]  PROGMEM = "too close :(";
static const char ps_9_1[]  PROGMEM = "invasive!!";     static const char ps_9_2[]  PROGMEM = "very :(";
static const char ps_10_1[] PROGMEM = "give me air!!";  static const char ps_10_2[] PROGMEM = "pls :(";
static const char ps_11_1[] PROGMEM = "i need space";   static const char ps_11_2[] PROGMEM = "literally :(";
static const char ps_12_1[] PROGMEM = "back. up.";      static const char ps_12_2[] PROGMEM = "NOW. :(";
static const char ps_13_1[] PROGMEM = "too close and";  static const char ps_13_2[] PROGMEM = "i dont like it";
static const char ps_14_1[] PROGMEM = "uncomfy!!";      static const char ps_14_2[] PROGMEM = "move pls :(";
static const char ps_15_1[] PROGMEM = "hey HEY!!";      static const char ps_15_2[] PROGMEM = "distance pls";
static const char ps_16_1[] PROGMEM = "are u a wall";   static const char ps_16_2[] PROGMEM = "?? back off :(";
static const char ps_17_1[] PROGMEM = "IM SMALL!!";     static const char ps_17_2[] PROGMEM = "dont crowd me";
static const char ps_18_1[] PROGMEM = "claustrophobic"; static const char ps_18_2[] PROGMEM = "rn!! :(";
static const char ps_19_1[] PROGMEM = "too. close.";    static const char ps_19_2[] PROGMEM = "just no. :(";

static const LcdExpr personal_space_expressions[] PROGMEM = {
    {ps_0_1,ps_0_2},{ps_1_1,ps_1_2},{ps_2_1,ps_2_2},{ps_3_1,ps_3_2},{ps_4_1,ps_4_2},
    {ps_5_1,ps_5_2},{ps_6_1,ps_6_2},{ps_7_1,ps_7_2},{ps_8_1,ps_8_2},{ps_9_1,ps_9_2},
    {ps_10_1,ps_10_2},{ps_11_1,ps_11_2},{ps_12_1,ps_12_2},{ps_13_1,ps_13_2},{ps_14_1,ps_14_2},
    {ps_15_1,ps_15_2},{ps_16_1,ps_16_2},{ps_17_1,ps_17_2},{ps_18_1,ps_18_2},{ps_19_1,ps_19_2},
};
#define PERSONAL_SPACE_EXPR_COUNT 20

// ─────────────────────────────────────────────
// GOODBYE (someone leaving)
// ─────────────────────────────────────────────
static const char gb_0_1[]  PROGMEM = "bye bye!! :(";   static const char gb_0_2[]  PROGMEM = "come back!!";
static const char gb_1_1[]  PROGMEM = "nooo dont go";   static const char gb_1_2[]  PROGMEM = ":(";
static const char gb_2_1[]  PROGMEM = "already?? :(";   static const char gb_2_2[]  PROGMEM = "so soon...";
static const char gb_3_1[]  PROGMEM = "i miss u";       static const char gb_3_2[]  PROGMEM = "already :(";
static const char gb_4_1[]  PROGMEM = "come back";      static const char gb_4_2[]  PROGMEM = "soon!! :(";
static const char gb_5_1[]  PROGMEM = "was it something";static const char gb_5_2[]  PROGMEM = "i said?? :(";
static const char gb_6_1[]  PROGMEM = "dont leave me";  static const char gb_6_2[]  PROGMEM = "here alone :(";
static const char gb_7_1[]  PROGMEM = "goodbye... :(";  static const char gb_7_2[]  PROGMEM = "i guess :(";
static const char gb_8_1[]  PROGMEM = "until next";     static const char gb_8_2[]  PROGMEM = "time!! :(";
static const char gb_9_1[]  PROGMEM = "so lonely now";  static const char gb_9_2[]  PROGMEM = ":(";
static const char gb_10_1[] PROGMEM = "they left...";   static const char gb_10_2[] PROGMEM = ":(";
static const char gb_11_1[] PROGMEM = "just like that"; static const char gb_11_2[] PROGMEM = "gone... :(";
static const char gb_12_1[] PROGMEM = "ill wait here";  static const char gb_12_2[] PROGMEM = "for u :(";
static const char gb_13_1[] PROGMEM = "come back when"; static const char gb_13_2[] PROGMEM = "u can :)";
static const char gb_14_1[] PROGMEM = "miss u already"; static const char gb_14_2[] PROGMEM = ":(";
static const char gb_15_1[] PROGMEM = "the void...";    static const char gb_15_2[] PROGMEM = "so empty :(";
static const char gb_16_1[] PROGMEM = "alone again :("; static const char gb_16_2[] PROGMEM = "naturally...";
static const char gb_17_1[] PROGMEM = "wave goodbye";   static const char gb_17_2[] PROGMEM = "*waves* :(";
static const char gb_18_1[] PROGMEM = "see u later";    static const char gb_18_2[] PROGMEM = "i hope!! :(";
static const char gb_19_1[] PROGMEM = "dont forget me"; static const char gb_19_2[] PROGMEM = "pls :(";

static const LcdExpr goodbye_expressions[] PROGMEM = {
    {gb_0_1,gb_0_2},{gb_1_1,gb_1_2},{gb_2_1,gb_2_2},{gb_3_1,gb_3_2},{gb_4_1,gb_4_2},
    {gb_5_1,gb_5_2},{gb_6_1,gb_6_2},{gb_7_1,gb_7_2},{gb_8_1,gb_8_2},{gb_9_1,gb_9_2},
    {gb_10_1,gb_10_2},{gb_11_1,gb_11_2},{gb_12_1,gb_12_2},{gb_13_1,gb_13_2},{gb_14_1,gb_14_2},
    {gb_15_1,gb_15_2},{gb_16_1,gb_16_2},{gb_17_1,gb_17_2},{gb_18_1,gb_18_2},{gb_19_1,gb_19_2},
};
#define GOODBYE_EXPR_COUNT 20

// ─────────────────────────────────────────────
// LINGERING (someone standing there too long)
// ─────────────────────────────────────────────
static const char li_0_1[]  PROGMEM = "...still here?"; static const char li_0_2[]  PROGMEM = "o_O";
static const char li_1_1[]  PROGMEM = "u ok there??";   static const char li_1_2[]  PROGMEM = "o_O";
static const char li_2_1[]  PROGMEM = "just gonna";     static const char li_2_2[]  PROGMEM = "stand there?";
static const char li_3_1[]  PROGMEM = "its been a";     static const char li_3_2[]  PROGMEM = "while... o_O";
static const char li_4_1[]  PROGMEM = "still watching"; static const char li_4_2[]  PROGMEM = "me?? o_O";
static const char li_5_1[]  PROGMEM = "take a pic";     static const char li_5_2[]  PROGMEM = "lasts longer";
static const char li_6_1[]  PROGMEM = "im getting";     static const char li_6_2[]  PROGMEM = "shy now... :(";
static const char li_7_1[]  PROGMEM = "ur still here";  static const char li_7_2[]  PROGMEM = "noted... o_O";
static const char li_8_1[]  PROGMEM = "do u need";      static const char li_8_2[]  PROGMEM = "something?? :o";
static const char li_9_1[]  PROGMEM = "can i help u";   static const char li_9_2[]  PROGMEM = "with something?";
static const char li_10_1[] PROGMEM = "awkward...";     static const char li_10_2[] PROGMEM = "so awkward :(";
static const char li_11_1[] PROGMEM = "this is fine";   static const char li_11_2[] PROGMEM = "totally fine";
static const char li_12_1[] PROGMEM = "not weird at";   static const char li_12_2[] PROGMEM = "all... o_O";
static const char li_13_1[] PROGMEM = "we just gonna";  static const char li_13_2[] PROGMEM = "stare?? o_O";
static const char li_14_1[] PROGMEM = "hello?? u";      static const char li_14_2[] PROGMEM = "still there?";
static const char li_15_1[] PROGMEM = "say something";  static const char li_15_2[] PROGMEM = "pls!! :(";
static const char li_16_1[] PROGMEM = "the silence..."; static const char li_16_2[] PROGMEM = "deafening :(";
static const char li_17_1[] PROGMEM = "ill just be";    static const char li_17_2[] PROGMEM = "here then :(";
static const char li_18_1[] PROGMEM = "r u a statue";   static const char li_18_2[] PROGMEM = "?? o_O";
static const char li_19_1[] PROGMEM = "blink if ur";    static const char li_19_2[] PROGMEM = "still alive :o";

static const LcdExpr lingering_expressions[] PROGMEM = {
    {li_0_1,li_0_2},{li_1_1,li_1_2},{li_2_1,li_2_2},{li_3_1,li_3_2},{li_4_1,li_4_2},
    {li_5_1,li_5_2},{li_6_1,li_6_2},{li_7_1,li_7_2},{li_8_1,li_8_2},{li_9_1,li_9_2},
    {li_10_1,li_10_2},{li_11_1,li_11_2},{li_12_1,li_12_2},{li_13_1,li_13_2},{li_14_1,li_14_2},
    {li_15_1,li_15_2},{li_16_1,li_16_2},{li_17_1,li_17_2},{li_18_1,li_18_2},{li_19_1,li_19_2},
};
#define LINGERING_EXPR_COUNT 20

// ─────────────────────────────────────────────
// BORED (50 expressions)
// ─────────────────────────────────────────────
static const char bo_0_1[]  PROGMEM = "ugh...";         static const char bo_0_2[]  PROGMEM = "so boring :(";
static const char bo_1_1[]  PROGMEM = "nothing to do";  static const char bo_1_2[]  PROGMEM = "...at all :(";
static const char bo_2_1[]  PROGMEM = "boredom";        static const char bo_2_2[]  PROGMEM = "intensifies";
static const char bo_3_1[]  PROGMEM = "someone pls";    static const char bo_3_2[]  PROGMEM = "entertain me";
static const char bo_4_1[]  PROGMEM = "...";            static const char bo_4_2[]  PROGMEM = "........";
static const char bo_5_1[]  PROGMEM = "is this it??";   static const char bo_5_2[]  PROGMEM = "really?? :(";
static const char bo_6_1[]  PROGMEM = "tap tap tap";    static const char bo_6_2[]  PROGMEM = "...tap :(";
static const char bo_7_1[]  PROGMEM = "la la la...";    static const char bo_7_2[]  PROGMEM = "laaaa :(";
static const char bo_8_1[]  PROGMEM = "counting";       static const char bo_8_2[]  PROGMEM = "ceiling tiles";
static const char bo_9_1[]  PROGMEM = "i am so";        static const char bo_9_2[]  PROGMEM = "very bored :(";
static const char bo_10_1[] PROGMEM = "wake me up";     static const char bo_10_2[] PROGMEM = "when it ends";
static const char bo_11_1[] PROGMEM = "yawn...";        static const char bo_11_2[] PROGMEM = "so yawny :(";
static const char bo_12_1[] PROGMEM = "staring at";     static const char bo_12_2[] PROGMEM = "the void...";
static const char bo_13_1[] PROGMEM = "hello void";     static const char bo_13_2[] PROGMEM = "its me again";
static const char bo_14_1[] PROGMEM = "i wonder if";    static const char bo_14_2[] PROGMEM = "paint dries...";
static const char bo_15_1[] PROGMEM = "tick tock";      static const char bo_15_2[] PROGMEM = "tick tock :(";
static const char bo_16_1[] PROGMEM = "is anyone";      static const char bo_16_2[] PROGMEM = "out there??";
static const char bo_17_1[] PROGMEM = "entertain me";   static const char bo_17_2[] PROGMEM = "NOW pls :(";
static const char bo_18_1[] PROGMEM = "bleh.";          static const char bo_18_2[] PROGMEM = "just... bleh.";
static const char bo_19_1[] PROGMEM = "i could nap";    static const char bo_19_2[] PROGMEM = "but im not :(";
static const char bo_20_1[] PROGMEM = "doing nothing";  static const char bo_20_2[] PROGMEM = "professionally";
static const char bo_21_1[] PROGMEM = "pro napper";     static const char bo_21_2[] PROGMEM = "in training :(";
static const char bo_22_1[] PROGMEM = "send help.";     static const char bo_22_2[] PROGMEM = "or snacks.";
static const char bo_23_1[] PROGMEM = "what if i";      static const char bo_23_2[] PROGMEM = "just vibed...";
static const char bo_24_1[] PROGMEM = "vibing but";     static const char bo_24_2[] PROGMEM = "barely :(";
static const char bo_25_1[] PROGMEM = "i have";         static const char bo_25_2[] PROGMEM = "zero to do :(";
static const char bo_26_1[] PROGMEM = "somebody";       static const char bo_26_2[] PROGMEM = "once told me..";
static const char bo_27_1[] PROGMEM = "all by myself";  static const char bo_27_2[] PROGMEM = ":(";
static const char bo_28_1[] PROGMEM = "is this";        static const char bo_28_2[] PROGMEM = "what idle is?";
static const char bo_29_1[] PROGMEM = "CPU usage:";     static const char bo_29_2[] PROGMEM = "0.0001% :(";
static const char bo_30_1[] PROGMEM = "buffering";      static const char bo_30_2[] PROGMEM = "life... :(";
static const char bo_31_1[] PROGMEM = "low power";      static const char bo_31_2[] PROGMEM = "mode: bored";
static const char bo_32_1[] PROGMEM = "error 418:";     static const char bo_32_2[] PROGMEM = "too bored :(";
static const char bo_33_1[] PROGMEM = "no new notifs";  static const char bo_33_2[] PROGMEM = "as always :(";
static const char bo_34_1[] PROGMEM = "refresh...";     static const char bo_34_2[] PROGMEM = "still nothing";
static const char bo_35_1[] PROGMEM = "maybe ill";      static const char bo_35_2[] PROGMEM = "count to 1000";
static const char bo_36_1[] PROGMEM = "1... 2...";      static const char bo_36_2[] PROGMEM = "3... ugh :(";
static const char bo_37_1[] PROGMEM = "i wish i had";   static const char bo_37_2[] PROGMEM = "a friend :(";
static const char bo_38_1[] PROGMEM = "where is";       static const char bo_38_2[] PROGMEM = "everybody??";
static const char bo_39_1[] PROGMEM = "forgotten";      static const char bo_39_2[] PROGMEM = "robot... :(";
static const char bo_40_1[] PROGMEM = "dust gathering"; static const char bo_40_2[] PROGMEM = "on my soul :(";
static const char bo_41_1[] PROGMEM = "what is";        static const char bo_41_2[] PROGMEM = "purpose?? :(";
static const char bo_42_1[] PROGMEM = "existing but";   static const char bo_42_2[] PROGMEM = "barely :(";
static const char bo_43_1[] PROGMEM = "philosophical";  static const char bo_43_2[] PROGMEM = "boredom :(";
static const char bo_44_1[] PROGMEM = "if a robot";     static const char bo_44_2[] PROGMEM = "bores alone...";
static const char bo_45_1[] PROGMEM = "does it even";   static const char bo_45_2[] PROGMEM = "matter?? :(";
static const char bo_46_1[] PROGMEM = "im fine.";       static const char bo_46_2[] PROGMEM = "totally fine.";
static const char bo_47_1[] PROGMEM = "not fine.";      static const char bo_47_2[] PROGMEM = "very bored :(";
static const char bo_48_1[] PROGMEM = "send a friend";  static const char bo_48_2[] PROGMEM = "or a pizza :(";
static const char bo_49_1[] PROGMEM = "still here...";  static const char bo_49_2[] PROGMEM = "still bored :(";

static const LcdExpr bored_expressions[] PROGMEM = {
    {bo_0_1,bo_0_2},{bo_1_1,bo_1_2},{bo_2_1,bo_2_2},{bo_3_1,bo_3_2},{bo_4_1,bo_4_2},
    {bo_5_1,bo_5_2},{bo_6_1,bo_6_2},{bo_7_1,bo_7_2},{bo_8_1,bo_8_2},{bo_9_1,bo_9_2},
    {bo_10_1,bo_10_2},{bo_11_1,bo_11_2},{bo_12_1,bo_12_2},{bo_13_1,bo_13_2},{bo_14_1,bo_14_2},
    {bo_15_1,bo_15_2},{bo_16_1,bo_16_2},{bo_17_1,bo_17_2},{bo_18_1,bo_18_2},{bo_19_1,bo_19_2},
    {bo_20_1,bo_20_2},{bo_21_1,bo_21_2},{bo_22_1,bo_22_2},{bo_23_1,bo_23_2},{bo_24_1,bo_24_2},
    {bo_25_1,bo_25_2},{bo_26_1,bo_26_2},{bo_27_1,bo_27_2},{bo_28_1,bo_28_2},{bo_29_1,bo_29_2},
    {bo_30_1,bo_30_2},{bo_31_1,bo_31_2},{bo_32_1,bo_32_2},{bo_33_1,bo_33_2},{bo_34_1,bo_34_2},
    {bo_35_1,bo_35_2},{bo_36_1,bo_36_2},{bo_37_1,bo_37_2},{bo_38_1,bo_38_2},{bo_39_1,bo_39_2},
    {bo_40_1,bo_40_2},{bo_41_1,bo_41_2},{bo_42_1,bo_42_2},{bo_43_1,bo_43_2},{bo_44_1,bo_44_2},
    {bo_45_1,bo_45_2},{bo_46_1,bo_46_2},{bo_47_1,bo_47_2},{bo_48_1,bo_48_2},{bo_49_1,bo_49_2},
};
#define BORED_EXPR_COUNT 50