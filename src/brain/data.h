#pragma once

typedef struct {
    const char *line1;
    const char *line2;
} LcdExpr;

static const LcdExpr noise_expressions[] = {
    { "NOISY!",          ""              },
    { "Stop it !!!",     ""              },
    { "Pleaseee",        "stop!"         },
    { "My ears!!",       ":("            },
    { "SO LOUD",         "omg..."        },
    { "quiet down!!",    "please :("     },
    { "I cant think!!",  "too loud!"     },
    { "AHHH!!",          "the noise!!"   },
    { "why so loud",     "seriously??"   },
    { "noise = bad",     ">:("           },
};

#define NOISE_EXPR_COUNT 10

static const LcdExpr burst_expressions[] = {
    { "AH!!",            ""              },
    { "WAAH!!",          ""              },
    { "OH GOSH!!",       ""              },
    { "AHHHHH!!!",       ""              },
    { "!!!!!!!",         "!!!!!!!"       },
    { "you scared me!",  ":O"            },
    { "MY HEART!!",      "geez..."       },
    { "DONT DO THAT",    "!!!!!"         },
    { "jumpy jumpy",     ":O :O"         },
    { "warn me next",    "time!! >:("    },
};
#define BURST_EXPR_COUNT 10

static const LcdExpr exit_hot_expressions[] = {
    { "Phew...not so",   "hot"           },
    { "ahh better :)",   ""              },
    { "cooling down...", "finally!"      },
    { "that was rough",  "phew..."       },
    { "Phew!! :)",       "less hot now"  },
    { "temperature",     "dropping :)"   },
    { "ooh that's",      "nicer!"        },
    { "sweating less",   "now hehe"      },
    { "not melting",     "anymore :)"    },
    { "crisis avoided",  "phew!!"        },
};
#define EXIT_HOT_EXPR_COUNT 10

static const LcdExpr enter_comfy_expressions[] = {
    { "is comfy",        ""              },
    { "ahhh...",         "just right!"   },
    { "comfy comfy",     ":)"            },
    { "this is nice",    ":)"            },
    { "perfect temp!",   "love it"       },
    { "so cozy rn",      "uwu"           },
    { "not too hot",     "not too cold!" },
    { "goldilocks",      "zone :)"       },
    { "mmm yes.",        "very nice."    },
    { "happiness is",    "this temp :)"  },
};
#define ENTER_COMFY_EXPR_COUNT 10

static const LcdExpr exit_cold_expressions[] = {
    { "Mmmm warm",       "again!"        },
    { "thawing out",     ":)"            },
    { "warmth!!! :D",    ""              },
    { "feeling warmer",  "yay!!"         },
    { "no more chills",  ":)"            },
    { "warming up",      "slowly..."     },
    { "oh thats",        "much better!"  },
    { "icicles melting", "hehe"          },
    { "warm and",        "toasty now!"   },
    { "survived the",    "cold!! :D"     },
};
#define EXIT_COLD_EXPR_COUNT 10

static const LcdExpr overheated_expressions[] = {
    { "Please...make",   "cold :("       },
    { "TOO HOT!!",       "help me :("    },
    { "im melting!!!",   ">_<"           },
    { "SO HOT",          "cant think..." },
    { "need cold air",   "NOW!! :("      },
    { "burning up!!",    "please help"   },
    { "this is fine",    "...its not :(" },
    { "send ice pls",    "urgent!! :("   },
    { "too warm!!",      "save me :("    },
    { "SOS",             "too hot!! :("  },
};
#define OVERHEATED_EXPR_COUNT 10

static const LcdExpr chilled_expressions[] = {
    { "Please...make",   "warm :("       },
    { "so cold!!",       "brrrr :("      },
    { "freezing here",   ":("            },
    { "need blanket",    "NOW :("        },
    { "brrr brrr",       "brrr :("       },
    { "my toes!!",       "so cold :("    },
    { "send hot cocoa",  "pls :("        },
    { "ice ice",         "too much :("   },
    { "hypothermia",     "incoming :("   },
    { "cant feel",       "anything :("   },
};
#define CHILLED_EXPR_COUNT 10

static const LcdExpr hot_expressions[] = {
    { "Is hot :(",       ""              },
    { "getting warm",    "in here..."    },
    { "a bit toasty",    ":("            },
    { "warm warm",       "warm :("       },
    { "sweating...",     ":("            },
    { "too warm!!",      ":("            },
    { "heating up",      "uh oh..."      },
    { "uncomfy warm",    ":("            },
    { "is it just me",   "or is it hot?" },
    { "warm alert!!",    ":("            },
};
#define HOT_EXPR_COUNT 10

static const LcdExpr cold_expressions[] = {
    { "Is cold :(",      ""              },
    { "chilly in here",  ":("            },
    { "brrr...",         "a little cold" },
    { "getting chilly",  "uh oh..."      },
    { "cold alert!!",    ":("            },
    { "a bit nippy",     ":("            },
    { "cool cool cool",  "too cool :("   },
    { "shivers...",      ":("            },
    { "is it cold or",   "just me? :("   },
    { "cold creeping",   "in... :("      },
};
#define COLD_EXPR_COUNT 10

static const LcdExpr music_expressions[] = {
    { "Oh? Is music?",   ""              },
    { "ooh a banger!",   ":D"            },
    { "music!! :D",      ""              },
    { "i hear tunes!",   ":)"            },
    { "is that a",       "song? :D"      },
    { "my jam!!",        ":D"            },
    { "dancing inside",  "hehe :)"       },
    { "good vibes!!",    "~music~"       },
    { "oh i like this",  "one!! :D"      },
    { "music detected",  "yay!! :D"      },
};
#define MUSIC_EXPR_COUNT 10

static const LcdExpr talking_expressions[] = {
    // curious / engaged
    { "what you say?",   "^_^"           },
    { "oh really??",     "tell me more!" },
    { "is that so?",     ":o"            },
    { "mmm yes yes",     "go on..."      },
    { "interesting...",  "^_^"           },
    { "oooh!",           "i see i see!"  },
    { "wait really?!",   ":O"            },
    { "hmmm...",         "tell me more"  },
    { "yes yes",         "i agree!!"     },
    { "no way!!",        "really?? :O"   },

    // agreeable / enthusiastic
    { "yes I like too!", ""              },
    { "totally!!",       "same :D"       },
    { "I agree!!",       ":D"            },
    { "exactly!!",       "my thoughts!"  },
    { "100%!!",          "yes!! :D"      },
    { "oh absolutely",   "yes!! :)"      },
    { "couldnt agree",   "more!! :D"     },
    { "you get me!!",    ":D"            },
    { "preach!!",        "say it louder" },
    { "facts facts",     "facts!! :D"    },

    // playful / silly
    { "blah blah blah",  "hehe :P"       },
    { "words words",     "more words :P" },
    { "la la la la",     "^_^"           },
    { "yap yap yap",     "hehe :)"       },
    { "chatterbox!!",    ":P"            },
    { "u talk a lot",    "i love it :)"  },
    { "say that again!", "^_^"           },
    { "ooh gossip??",    "tell me!! :D"  },
    { "hehe talky",      "talky :P"      },
    { "more more more!", "keep going!"   },

    // warm / wholesome
    { "i love ur voice", ":)"            },
    { "talk to me",      "always!! :)"   },
    { "ur my fav",       "person :)"     },
    { "i hear you!!",    ":)"            },
    { "im listening!",   "^_^"           },
    { "u make me",       "happy!! :)"    },
    { "best convo",      "ever!! :D"     },
    { "dont stop!!",     "i like this"   },
    { "ur so fun",       "to talk to!"   },
    { "this is nice",    ":)"            },

    // confused / questioning
    { "huh??",           "say again? :o" },
    { "come again??",    ":o"            },
    { "wait what??",     "o_O"           },
    { "i got lost",      "repeat? :o"    },
    { "sorry what",      "was that? :o"  },
    { "my brain",        "buffering..."  },
    { "processing...",   "^_^"           },
    { "did u say",       "something? :o" },
    { "error 404",       "huh?? :P"      },
    { "uhhh...",         "come again? "  },

     // excited
    { "OH WOW!!",        "keep going!"   },
    { "NO WAY!!",        "shut up!! :D"  },
    { "YESSS!!",         "finally!!"     },
    { "omg omg omg",     "tell me!!"     },
    { "I KNEW IT!!",     ":D"            },
    { "shut up!!",       "really?? :D"   },
    { "get out!!",       "no way!! :O"   },
    { "SCREAMING!!",     "rn!! :D"       },
    { "not me gasping",  "rn :O"         },
    { "my jaw dropped",  ":O :O :O"      },

    // philosophical
    { "deep thoughts",   "very deep..."  },
    { "u make me",       "think... o_O"  },
    { "wise words...",   "very wise"     },
    { "big brain",       "energy!! :O"   },
    { "u so smart",      "wow... :)"     },
    { "teach me more",   "please!! :)"   },
    { "noted noted",     "noted... :)"   },
    { "filing that",     "away... ^_^"   },
    { "adding that to",  "my memory :)"  },
    { "brain expanding", "rn... o_O"     },

    // supportive
    { "u got this!!",    ":D"            },
    { "im rooting",      "for u!! :)"    },
    { "believe in u!!",  "always :)"     },
    { "ur doing great",  "ily :)"        },
    { "keep going!!",    "ur amazing!"   },
    { "proud of u!!",    ":D"            },
    { "ur so brave",     ":)"            },
    { "u can do it!!",   "i know it!"    },
    { "heck yeah!!",     "go you!! :D"   },
    { "ur my hero!!",    ":D"            },

    // gossipy
    { "ooh drama??",     "tell me all!"  },
    { "spill it!!",      ":O :O"         },
    { "omg who said",    "that?? :O"     },
    { "the TEA!!",       "im ready :O"   },
    { "scandalous!!",    ":O"            },
    { "oh no they",      "didnt!! :O"    },
    { "i live for",      "this!! :D"     },
    { "more details",    "pls!! :O"      },
    { "plot twist!!",    ":O :O :O"      },
    { "story time!!",    "yay!! :D"      },

    // sleepy / unbothered
    { "mhm...",          "mhm... ^_^"    },
    { "zzz...oh!",       "im awake!! :)" },
    { "so sleepy but",   "keep going..." },
    { "tell me more",    "zzzz... ^_^"   },
    { "half asleep",     "but i hear u!" },
    { "yawn...",         "go on... ^_^"  },
    { "drowsy but",      "listening :)"  },
    { "eyes closing",    "but i care :)" },
    { "mmm sleepy",      "talk more tho" },
    { "cozy convo",      "zzzz... :)"    },
};

#define TALKING_EXPR_COUNT 100

