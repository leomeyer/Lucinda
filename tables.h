#ifndef __TABLES_H
#define __TABLES_H

#include "Arduino.h"

/*******************************************************
* Constant Table Definitions
*******************************************************/

PROGMEM const wavetable_t WAVE_SINE = {
0, 3, 6, 9, 12, 15, 18, 21, 25, 28, 31, 34, 37, 40, 43, 47, 50, 53, 56, 59, 62, 65, 69, 72, 75, 78, 81, 84, 87, 90, 94, 97, 100, 
103, 106, 109, 112, 115, 119, 122, 125, 128, 131, 134, 137, 140, 144, 147, 150, 153, 156, 159, 162, 165, 168, 171, 175, 178, 181, 184, 187, 190, 193, 196, 199, 
202, 205, 209, 212, 215, 218, 221, 224, 227, 230, 233, 236, 239, 242, 245, 248, 251, 254, 257, 260, 264, 267, 270, 273, 276, 279, 282, 285, 288, 291, 294, 297, 
300, 303, 306, 309, 312, 315, 318, 321, 324, 327, 330, 333, 336, 339, 342, 344, 347, 350, 353, 356, 359, 362, 365, 368, 371, 374, 377, 380, 383, 386, 388, 391, 
394, 397, 400, 403, 406, 409, 412, 414, 417, 420, 423, 426, 429, 432, 434, 437, 440, 443, 446, 449, 451, 454, 457, 460, 463, 465, 468, 471, 474, 477, 479, 482, 
485, 488, 490, 493, 496, 499, 501, 504, 507, 510, 512, 515, 518, 521, 523, 526, 529, 531, 534, 537, 539, 542, 545, 547, 550, 553, 555, 558, 561, 563, 566, 568, 
571, 574, 576, 579, 581, 584, 587, 589, 592, 594, 597, 599, 602, 604, 607, 609, 612, 615, 617, 620, 622, 625, 627, 629, 632, 634, 637, 639, 642, 644, 647, 649, 
652, 654, 656, 659, 661, 664, 666, 668, 671, 673, 675, 678, 680, 682, 685, 687, 689, 692, 694, 696, 699, 701, 703, 706, 708, 710, 712, 715, 717, 719, 721, 724, 
726, 728, 730, 732, 735, 737, 739, 741, 743, 745, 748, 750, 752, 754, 756, 758, 760, 762, 765, 767, 769, 771, 773, 775, 777, 779, 781, 783, 785, 787, 789, 791, 
793, 795, 797, 799, 801, 803, 805, 807, 809, 811, 813, 814, 816, 818, 820, 822, 824, 826, 828, 829, 831, 833, 835, 837, 839, 840, 842, 844, 846, 847, 849, 851, 
853, 854, 856, 858, 860, 861, 863, 865, 866, 868, 870, 871, 873, 875, 876, 878, 879, 881, 883, 884, 886, 887, 889, 890, 892, 894, 895, 897, 898, 900, 901, 903, 
904, 906, 907, 908, 910, 911, 913, 914, 916, 917, 918, 920, 921, 922, 924, 925, 927, 928, 929, 930, 932, 933, 934, 936, 937, 938, 939, 941, 942, 943, 944, 946, 
947, 948, 949, 950, 951, 953, 954, 955, 956, 957, 958, 959, 960, 961, 963, 964, 965, 966, 967, 968, 969, 970, 971, 972, 973, 974, 975, 976, 977, 978, 978, 979, 
980, 981, 982, 983, 984, 985, 986, 986, 987, 988, 989, 990, 990, 991, 992, 993, 994, 994, 995, 996, 997, 997, 998, 999, 999, 1000, 1001, 1001, 1002, 1003, 1003, 1004, 
1004, 1005, 1006, 1006, 1007, 1007, 1008, 1008, 1009, 1009, 1010, 1010, 1011, 1011, 1012, 1012, 1013, 1013, 1014, 1014, 1015, 1015, 1015, 1016, 1016, 1017, 1017, 1017, 1018, 1018, 1018, 1019, 
1019, 1019, 1019, 1020, 1020, 1020, 1020, 1021, 1021, 1021, 1021, 1022, 1022, 1022, 1022, 1022, 1022, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 
1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023, 1022, 1022, 1022, 1022, 1022, 1022, 1021, 1021, 1021, 1021, 1020, 1020, 1020, 1020, 1019, 1019, 1019, 1019, 
1018, 1018, 1018, 1017, 1017, 1017, 1016, 1016, 1015, 1015, 1015, 1014, 1014, 1013, 1013, 1012, 1012, 1011, 1011, 1011, 1010, 1009, 1009, 1008, 1008, 1007, 1007, 1006, 1006, 1005, 1004, 1004, 
1003, 1003, 1002, 1001, 1001, 1000, 999, 999, 998, 997, 997, 996, 995, 994, 994, 993, 992, 991, 990, 990, 989, 988, 987, 986, 986, 985, 984, 983, 982, 981, 980, 979, 
979, 978, 977, 976, 975, 974, 973, 972, 971, 970, 969, 968, 967, 966, 965, 964, 963, 962, 960, 959, 958, 957, 956, 955, 954, 953, 951, 950, 949, 948, 947, 946, 
944, 943, 942, 941, 939, 938, 937, 936, 934, 933, 932, 931, 929, 928, 927, 925, 924, 922, 921, 920, 918, 917, 916, 914, 913, 911, 910, 908, 907, 906, 904, 903, 
901, 900, 898, 897, 895, 894, 892, 890, 889, 887, 886, 884, 883, 881, 879, 878, 876, 875, 873, 871, 870, 868, 866, 865, 863, 861, 860, 858, 856, 854, 853, 851, 
849, 847, 846, 844, 842, 840, 839, 837, 835, 833, 831, 829, 828, 826, 824, 822, 820, 818, 816, 814, 813, 811, 809, 807, 805, 803, 801, 799, 797, 795, 793, 791, 
789, 787, 785, 783, 781, 779, 777, 775, 773, 771, 769, 767, 765, 762, 760, 758, 756, 754, 752, 750, 748, 745, 743, 741, 739, 737, 735, 732, 730, 728, 726, 724, 
721, 719, 717, 715, 712, 710, 708, 706, 703, 701, 699, 696, 694, 692, 690, 687, 685, 683, 680, 678, 675, 673, 671, 668, 666, 664, 661, 659, 656, 654, 652, 649, 
647, 644, 642, 639, 637, 634, 632, 630, 627, 625, 622, 620, 617, 615, 612, 610, 607, 604, 602, 599, 597, 594, 592, 589, 587, 584, 581, 579, 576, 574, 571, 568, 
566, 563, 561, 558, 555, 553, 550, 547, 545, 542, 539, 537, 534, 531, 529, 526, 523, 521, 518, 515, 512, 510, 507, 504, 502, 499, 496, 493, 491, 488, 485, 482, 
479, 477, 474, 471, 468, 466, 463, 460, 457, 454, 452, 449, 446, 443, 440, 437, 435, 432, 429, 426, 423, 420, 417, 415, 412, 409, 406, 403, 400, 397, 394, 391, 
389, 386, 383, 380, 377, 374, 371, 368, 365, 362, 359, 356, 353, 350, 347, 345, 342, 339, 336, 333, 330, 327, 324, 321, 318, 315, 312, 309, 306, 303, 300, 297, 
294, 291, 288, 285, 282, 279, 276, 273, 270, 267, 264, 261, 257, 254, 251, 248, 245, 242, 239, 236, 233, 230, 227, 224, 221, 218, 215, 212, 209, 205, 202, 199, 
196, 193, 190, 187, 184, 181, 178, 175, 172, 168, 165, 162, 159, 156, 153, 150, 147, 144, 140, 137, 134, 131, 128, 125, 122, 119, 116, 112, 109, 106, 103, 100, 
97, 94, 91, 87, 84, 81, 78, 75, 72, 69, 65, 62, 59, 56, 53, 50, 47, 44, 40, 37, 34, 31, 28, 25, 22, 18, 15, 12, 9, 6, 3
};

PROGMEM const wavetable_t WAVE_TRIANGLE = {
0, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 
65, 67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93, 95, 97, 99, 101, 103, 105, 107, 109, 111, 113, 115, 117, 119, 121, 123, 125, 127, 
129, 131, 133, 135, 137, 139, 141, 143, 145, 147, 149, 151, 153, 155, 157, 159, 161, 163, 165, 167, 169, 171, 173, 175, 177, 179, 181, 183, 185, 187, 189, 191, 
193, 195, 197, 199, 201, 203, 205, 207, 209, 211, 213, 215, 217, 219, 221, 223, 225, 227, 229, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255, 
257, 259, 261, 263, 265, 267, 269, 271, 273, 275, 277, 279, 281, 283, 285, 287, 289, 291, 293, 295, 297, 299, 301, 303, 305, 307, 309, 311, 313, 315, 317, 319, 
321, 323, 325, 327, 329, 331, 333, 335, 337, 339, 341, 343, 345, 347, 349, 351, 353, 355, 357, 359, 361, 363, 365, 367, 369, 371, 373, 375, 377, 379, 381, 383, 
385, 387, 389, 391, 393, 395, 397, 399, 401, 403, 405, 407, 409, 411, 413, 415, 417, 419, 421, 423, 425, 427, 429, 431, 433, 435, 437, 439, 441, 443, 445, 447, 
449, 451, 453, 455, 457, 459, 461, 463, 465, 467, 469, 471, 473, 475, 477, 479, 481, 483, 485, 487, 489, 491, 493, 495, 497, 499, 501, 503, 505, 507, 509, 511, 
513, 515, 517, 519, 521, 523, 525, 527, 529, 531, 533, 535, 537, 539, 541, 543, 545, 547, 549, 551, 553, 555, 557, 559, 561, 563, 565, 567, 569, 571, 573, 575, 
577, 579, 581, 583, 585, 587, 589, 591, 593, 595, 597, 599, 601, 603, 605, 607, 609, 611, 613, 615, 617, 619, 621, 623, 625, 627, 629, 631, 633, 635, 637, 639, 
641, 643, 645, 647, 649, 651, 653, 655, 657, 659, 661, 663, 665, 667, 669, 671, 673, 675, 677, 679, 681, 683, 685, 687, 689, 691, 693, 695, 697, 699, 701, 703, 
705, 707, 709, 711, 713, 715, 717, 719, 721, 723, 725, 727, 729, 731, 733, 735, 737, 739, 741, 743, 745, 747, 749, 751, 753, 755, 757, 759, 761, 763, 765, 767, 
769, 771, 773, 775, 777, 779, 781, 783, 785, 787, 789, 791, 793, 795, 797, 799, 801, 803, 805, 807, 809, 811, 813, 815, 817, 819, 821, 823, 825, 827, 829, 831, 
833, 835, 837, 839, 841, 843, 845, 847, 849, 851, 853, 855, 857, 859, 861, 863, 865, 867, 869, 871, 873, 875, 877, 879, 881, 883, 885, 887, 889, 891, 893, 895, 
897, 899, 901, 903, 905, 907, 909, 911, 913, 915, 917, 919, 921, 923, 925, 927, 929, 931, 933, 935, 937, 939, 941, 943, 945, 947, 949, 951, 953, 955, 957, 959, 
961, 963, 965, 967, 969, 971, 973, 975, 977, 979, 981, 983, 985, 987, 989, 991, 993, 995, 997, 999, 1001, 1003, 1005, 1007, 1009, 1011, 1013, 1015, 1017, 1019, 1021, 1023, 
1021, 1019, 1017, 1015, 1013, 1011, 1009, 1007, 1005, 1003, 1001, 999, 997, 995, 993, 991, 989, 987, 985, 983, 981, 979, 977, 975, 973, 971, 969, 967, 965, 963, 961, 959, 
957, 955, 953, 951, 949, 947, 945, 943, 941, 939, 937, 935, 933, 931, 929, 927, 925, 923, 921, 919, 917, 915, 913, 911, 909, 907, 905, 903, 901, 899, 897, 895, 
893, 891, 889, 887, 885, 883, 881, 879, 877, 875, 873, 871, 869, 867, 865, 863, 861, 859, 857, 855, 853, 851, 849, 847, 845, 843, 841, 839, 837, 835, 833, 831, 
829, 827, 825, 823, 821, 819, 817, 815, 813, 811, 809, 807, 805, 803, 801, 799, 797, 795, 793, 791, 789, 787, 785, 783, 781, 779, 777, 775, 773, 771, 769, 767, 
765, 763, 761, 759, 757, 755, 753, 751, 749, 747, 745, 743, 741, 739, 737, 735, 733, 731, 729, 727, 725, 723, 721, 719, 717, 715, 713, 711, 709, 707, 705, 703, 
701, 699, 697, 695, 693, 691, 689, 687, 685, 683, 681, 679, 677, 675, 673, 671, 669, 667, 665, 663, 661, 659, 657, 655, 653, 651, 649, 647, 645, 643, 641, 639, 
637, 635, 633, 631, 629, 627, 625, 623, 621, 619, 617, 615, 613, 611, 609, 607, 605, 603, 601, 599, 597, 595, 593, 591, 589, 587, 585, 583, 581, 579, 577, 575, 
573, 571, 569, 567, 565, 563, 561, 559, 557, 555, 553, 551, 549, 547, 545, 543, 541, 539, 537, 535, 533, 531, 529, 527, 525, 523, 521, 519, 517, 515, 513, 511, 
509, 507, 505, 503, 501, 499, 497, 495, 493, 491, 489, 487, 485, 483, 481, 479, 477, 475, 473, 471, 469, 467, 465, 463, 461, 459, 457, 455, 453, 451, 449, 447, 
445, 443, 441, 439, 437, 435, 433, 431, 429, 427, 425, 423, 421, 419, 417, 415, 413, 411, 409, 407, 405, 403, 401, 399, 397, 395, 393, 391, 389, 387, 385, 383, 
381, 379, 377, 375, 373, 371, 369, 367, 365, 363, 361, 359, 357, 355, 353, 351, 349, 347, 345, 343, 341, 339, 337, 335, 333, 331, 329, 327, 325, 323, 321, 319, 
317, 315, 313, 311, 309, 307, 305, 303, 301, 299, 297, 295, 293, 291, 289, 287, 285, 283, 281, 279, 277, 275, 273, 271, 269, 267, 265, 263, 261, 259, 257, 255, 
253, 251, 249, 247, 245, 243, 241, 239, 237, 235, 233, 231, 229, 227, 225, 223, 221, 219, 217, 215, 213, 211, 209, 207, 205, 203, 201, 199, 197, 195, 193, 191, 
189, 187, 185, 183, 181, 179, 177, 175, 173, 171, 169, 167, 165, 163, 161, 159, 157, 155, 153, 151, 149, 147, 145, 143, 141, 139, 137, 135, 133, 131, 129, 127, 
125, 123, 121, 119, 117, 115, 113, 111, 109, 107, 105, 103, 101, 99, 97, 95, 93, 91, 89, 87, 85, 83, 81, 79, 77, 75, 73, 71, 69, 67, 65, 63, 
61, 59, 57, 55, 53, 51, 49, 47, 45, 43, 41, 39, 37, 35, 33, 31, 29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1
};

PROGMEM const wavetable_t WAVE_FLICKER = {
1, 576, 197, 827, 598, 490, 358, 916, 841, 763, 178, 878, 726, 525, 310, 15, 93, 372, 150, 169, 1011, 455, 121, 4, 9, 386, 543, 584, 615, 621, 170, 678, 461, 
360, 58, 621, 801, 821, 531, 308, 896, 743, 977, 947, 551, 145, 472, 240, 882, 214, 797, 863, 1019, 1022, 625, 401, 272, 304, 859, 24, 384, 94, 692, 57, 8, 
939, 282, 279, 601, 707, 856, 743, 496, 210, 760, 479, 468, 970, 761, 110, 612, 394, 751, 622, 585, 369, 155, 230, 434, 821, 528, 1012, 768, 353, 172, 672, 503, 
65, 715, 516, 150, 971, 144, 925, 708, 310, 436, 71, 988, 698, 156, 897, 840, 595, 195, 181, 835, 486, 159, 515, 748, 414, 286, 581, 697, 773, 738, 486, 125, 
376, 853, 35, 528, 678, 436, 107, 971, 942, 562, 353, 482, 383, 866, 324, 466, 278, 1005, 304, 756, 580, 200, 778, 858, 406, 512, 910, 28, 1017, 585, 51, 543, 
198, 862, 641, 672, 202, 861, 126, 112, 760, 321, 962, 292, 344, 143, 749, 853, 724, 614, 764, 258, 147, 1, 62, 824, 872, 215, 118, 565, 14, 116, 464, 769, 
701, 555, 75, 446, 206, 712, 297, 446, 237, 591, 544, 643, 163, 515, 985, 711, 946, 194, 343, 182, 1018, 467, 1020, 99, 639, 96, 447, 952, 49, 915, 296, 232, 
786, 420, 206, 642, 618, 462, 477, 611, 649, 874, 847, 639, 737, 578, 383, 188, 754, 567, 925, 248, 193, 618, 714, 598, 359, 505, 82, 757, 626, 634, 707, 823, 
152, 589, 887, 932, 628, 744, 44, 683, 998, 322, 582, 312, 177, 111, 889, 870, 761, 158, 334, 81, 78, 655, 838, 557, 458, 418, 305, 476, 512, 156, 330, 754, 
321, 845, 981, 893, 741, 306, 965, 130, 67, 803, 536, 623, 978, 73, 895, 668, 329, 107, 516, 232, 296, 941, 563, 678, 117, 503, 387, 508, 811, 520, 391, 703, 
544, 620, 404, 6, 724, 102, 637, 883, 502, 764, 508, 388, 803, 565, 365, 977, 645, 180, 382, 134, 760, 973, 626, 28, 337, 57, 653, 134, 866, 884, 610, 738, 
873, 15, 129, 724, 631, 222, 67, 172, 638, 348, 326, 376, 676, 820, 825, 538, 625, 816, 921, 148, 644, 411, 259, 139, 874, 67, 437, 586, 309, 560, 230, 318, 
113, 826, 137, 290, 806, 915, 807, 760, 629, 369, 876, 233, 883, 234, 255, 554, 1007, 55, 83, 536, 436, 96, 264, 912, 238, 149, 127, 953, 81, 48, 60, 344, 
935, 407, 442, 967, 856, 546, 861, 709, 406, 265, 4, 537, 976, 407, 246, 599, 261, 699, 967, 445, 910, 7, 962, 615, 804, 589, 145, 227, 391, 4, 427, 84, 
675, 874, 66, 829, 677, 707, 821, 542, 701, 146, 705, 744, 795, 31, 888, 659, 722, 87, 564, 969, 60, 281, 148, 1004, 634, 298, 943, 375, 710, 223, 159, 246, 
533, 923, 108, 923, 451, 81, 800, 175, 996, 793, 890, 215, 467, 3, 767, 116, 414, 318, 1015, 39, 257, 193, 253, 157, 634, 905, 960, 200, 797, 660, 671, 930, 
465, 942, 679, 154, 650, 582, 431, 964, 553, 591, 548, 261, 406, 358, 37, 813, 201, 71, 398, 604, 72, 202, 159, 659, 464, 618, 713, 451, 700, 405, 854, 605, 
204, 971, 896, 400, 1010, 189, 916, 587, 452, 641, 724, 50, 292, 266, 417, 915, 726, 745, 916, 402, 406, 924, 315, 397, 583, 361, 750, 762, 753, 756, 142, 204, 
278, 696, 932, 376, 529, 111, 928, 207, 529, 669, 448, 703, 92, 81, 77, 28, 363, 314, 713, 145, 403, 69, 691, 741, 203, 709, 629, 669, 556, 100, 557, 50, 
996, 474, 992, 744, 543, 695, 708, 380, 397, 51, 828, 173, 62, 317, 802, 217, 329, 495, 9, 449, 519, 619, 775, 410, 357, 862, 963, 637, 1020, 54, 575, 883, 
395, 313, 290, 27, 626, 400, 19, 31, 466, 877, 958, 411, 744, 625, 826, 895, 595, 608, 80, 811, 472, 604, 602, 582, 834, 688, 351, 10, 273, 349, 237, 788, 
380, 889, 119, 742, 643, 914, 187, 547, 922, 798, 987, 201, 922, 815, 975, 868, 910, 643, 189, 631, 271, 256, 749, 806, 174, 730, 492, 83, 825, 875, 127, 314, 
586, 483, 779, 196, 744, 1017, 15, 662, 707, 178, 73, 281, 692, 858, 569, 379, 797, 237, 652, 236, 209, 993, 288, 23, 786, 155, 48, 9, 356, 658, 351, 424, 
426, 92, 557, 715, 345, 672, 896, 547, 583, 55, 476, 265, 436, 883, 497, 89, 578, 725, 796, 884, 870, 299, 884, 659, 764, 847, 783, 891, 929, 933, 533, 450, 
110, 362, 841, 437, 173, 0, 672, 791, 65, 91, 394, 699, 826, 157, 146, 49, 354, 18, 1000, 662, 54, 935, 652, 441, 21, 248, 400, 669, 799, 23, 845, 141, 
648, 563, 1006, 474, 219, 307, 800, 350, 491, 622, 104, 1007, 773, 154, 466, 727, 1021, 793, 656, 635, 967, 703, 296, 580, 297, 560, 728, 252, 559, 503, 973, 685, 
782, 637, 456, 817, 762, 1011, 209, 643, 930, 604, 939, 517, 500, 460, 909, 962, 187, 257, 207, 747, 962, 639, 42, 656, 35, 569, 557, 456, 62, 1018, 130, 614, 
51, 176, 675, 340, 323, 668, 419, 437, 226, 694, 170, 508, 519, 821, 445, 4, 347, 384, 131, 846, 750, 911, 658, 665, 526, 750, 754, 979, 476, 371, 114, 925, 
840, 465, 111, 889, 778, 40, 426, 957, 69, 168, 216, 119, 604, 121, 632, 593, 706, 748, 936, 685, 305, 827, 386, 1020, 790, 209, 174, 397, 185, 594, 200, 982, 
194, 390, 310, 123, 202, 47, 788, 778, 901, 1, 458, 436, 819, 471, 506, 766, 243, 572, 94, 943, 914, 876, 61, 502, 646, 764, 773, 261, 930, 810, 204, 565, 
52, 534, 808, 720, 24, 748, 566, 935, 895, 815, 312, 404, 492, 53, 666, 0, 786, 773, 224, 158, 58, 686, 33, 353, 713, 816, 446, 1004, 650, 302, 487, 894, 
81, 103, 146, 146, 939, 315, 382, 832, 47, 832, 245, 918, 262, 275, 212, 234, 865, 894, 908, 864, 623, 41, 177, 187, 364, 459, 189, 915, 637, 558, 932
};

PROGMEM const wavetable_t WAVE_LINEAR = {
0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 
33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 
65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 
97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 
129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 
161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 
193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 
225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 
257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 
289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 
321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 
353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 
385, 386, 387, 388, 389, 390, 391, 392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412, 413, 414, 415, 416, 
417, 418, 419, 420, 421, 422, 423, 424, 425, 426, 427, 428, 429, 430, 431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446, 447, 448, 
449, 450, 451, 452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 463, 464, 465, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 476, 477, 478, 479, 480, 
481, 482, 483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494, 495, 496, 497, 498, 499, 500, 501, 502, 503, 504, 505, 506, 507, 508, 509, 510, 511, 512, 
513, 514, 515, 516, 517, 518, 519, 520, 521, 522, 523, 524, 525, 526, 527, 528, 529, 530, 531, 532, 533, 534, 535, 536, 537, 538, 539, 540, 541, 542, 543, 544, 
545, 546, 547, 548, 549, 550, 551, 552, 553, 554, 555, 556, 557, 558, 559, 560, 561, 562, 563, 564, 565, 566, 567, 568, 569, 570, 571, 572, 573, 574, 575, 576, 
577, 578, 579, 580, 581, 582, 583, 584, 585, 586, 587, 588, 589, 590, 591, 592, 593, 594, 595, 596, 597, 598, 599, 600, 601, 602, 603, 604, 605, 606, 607, 608, 
609, 610, 611, 612, 613, 614, 615, 616, 617, 618, 619, 620, 621, 622, 623, 624, 625, 626, 627, 628, 629, 630, 631, 632, 633, 634, 635, 636, 637, 638, 639, 640, 
641, 642, 643, 644, 645, 646, 647, 648, 649, 650, 651, 652, 653, 654, 655, 656, 657, 658, 659, 660, 661, 662, 663, 664, 665, 666, 667, 668, 669, 670, 671, 672, 
673, 674, 675, 676, 677, 678, 679, 680, 681, 682, 683, 684, 685, 686, 687, 688, 689, 690, 691, 692, 693, 694, 695, 696, 697, 698, 699, 700, 701, 702, 703, 704, 
705, 706, 707, 708, 709, 710, 711, 712, 713, 714, 715, 716, 717, 718, 719, 720, 721, 722, 723, 724, 725, 726, 727, 728, 729, 730, 731, 732, 733, 734, 735, 736, 
737, 738, 739, 740, 741, 742, 743, 744, 745, 746, 747, 748, 749, 750, 751, 752, 753, 754, 755, 756, 757, 758, 759, 760, 761, 762, 763, 764, 765, 766, 767, 768, 
769, 770, 771, 772, 773, 774, 775, 776, 777, 778, 779, 780, 781, 782, 783, 784, 785, 786, 787, 788, 789, 790, 791, 792, 793, 794, 795, 796, 797, 798, 799, 800, 
801, 802, 803, 804, 805, 806, 807, 808, 809, 810, 811, 812, 813, 814, 815, 816, 817, 818, 819, 820, 821, 822, 823, 824, 825, 826, 827, 828, 829, 830, 831, 832, 
833, 834, 835, 836, 837, 838, 839, 840, 841, 842, 843, 844, 845, 846, 847, 848, 849, 850, 851, 852, 853, 854, 855, 856, 857, 858, 859, 860, 861, 862, 863, 864, 
865, 866, 867, 868, 869, 870, 871, 872, 873, 874, 875, 876, 877, 878, 879, 880, 881, 882, 883, 884, 885, 886, 887, 888, 889, 890, 891, 892, 893, 894, 895, 896, 
897, 898, 899, 900, 901, 902, 903, 904, 905, 906, 907, 908, 909, 910, 911, 912, 913, 914, 915, 916, 917, 918, 919, 920, 921, 922, 923, 924, 925, 926, 927, 928, 
929, 930, 931, 932, 933, 934, 935, 936, 937, 938, 939, 940, 941, 942, 943, 944, 945, 946, 947, 948, 949, 950, 951, 952, 953, 954, 955, 956, 957, 958, 959, 960, 
961, 962, 963, 964, 965, 966, 967, 968, 969, 970, 971, 972, 973, 974, 975, 976, 977, 978, 979, 980, 981, 982, 983, 984, 985, 986, 987, 988, 989, 990, 991, 992, 
993, 994, 995, 996, 997, 998, 999, 1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010, 1011, 1012, 1013, 1014, 1015, 1016, 1017, 1018, 1019, 1020, 1021, 1022, 1023
};

// exponential correction curve for the human eye
// formula: f0 = 0; fi = max(1, (int)(pow(2.0, 10.0 * (i + 1) / 256)) - 1) for i = 1..1023
PROGMEM const uint16_t eye_correction[1024] = {
0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 
6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 
9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 
12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 
15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 
20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 
25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 30, 30, 30, 30, 31, 31, 
31, 31, 31, 32, 32, 32, 32, 33, 33, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 35, 36, 36, 36, 36, 37, 37, 37, 37, 38, 38, 38, 39, 
39, 39, 39, 40, 40, 40, 40, 41, 41, 41, 42, 42, 42, 42, 43, 43, 43, 44, 44, 44, 45, 45, 45, 46, 46, 46, 47, 47, 47, 48, 48, 48, 
49, 49, 49, 50, 50, 50, 51, 51, 51, 52, 52, 52, 53, 53, 53, 54, 54, 55, 55, 55, 56, 56, 57, 57, 57, 58, 58, 59, 59, 59, 60, 60, 
61, 61, 61, 62, 62, 63, 63, 64, 64, 65, 65, 65, 66, 66, 67, 67, 68, 68, 69, 69, 70, 70, 71, 71, 72, 72, 73, 73, 74, 74, 75, 75, 
76, 76, 77, 77, 78, 78, 79, 79, 80, 80, 81, 82, 82, 83, 83, 84, 84, 85, 86, 86, 87, 87, 88, 89, 89, 90, 90, 91, 92, 92, 93, 94, 
94, 95, 96, 96, 97, 98, 98, 99, 100, 100, 101, 102, 102, 103, 104, 105, 105, 106, 107, 107, 108, 109, 110, 110, 111, 112, 113, 114, 114, 115, 116, 117, 
117, 118, 119, 120, 121, 122, 122, 123, 124, 125, 126, 127, 128, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 138, 139, 140, 141, 142, 143, 144, 145, 
146, 147, 148, 149, 150, 151, 152, 153, 154, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 167, 168, 169, 170, 171, 172, 173, 175, 176, 177, 178, 180, 181, 
182, 183, 184, 186, 187, 188, 190, 191, 192, 194, 195, 196, 198, 199, 200, 202, 203, 204, 206, 207, 209, 210, 211, 213, 214, 216, 217, 219, 220, 222, 223, 225, 
226, 228, 229, 231, 233, 234, 236, 237, 239, 241, 242, 244, 246, 247, 249, 251, 252, 254, 256, 258, 259, 261, 263, 265, 267, 268, 270, 272, 274, 276, 278, 280, 
281, 283, 285, 287, 289, 291, 293, 295, 297, 299, 301, 303, 305, 308, 310, 312, 314, 316, 318, 320, 322, 325, 327, 329, 331, 334, 336, 338, 341, 343, 345, 348, 
350, 352, 355, 357, 360, 362, 364, 367, 369, 372, 375, 377, 380, 382, 385, 387, 390, 393, 395, 398, 401, 404, 406, 409, 412, 415, 418, 420, 423, 426, 429, 432, 
435, 438, 441, 444, 447, 450, 453, 456, 459, 462, 465, 469, 472, 475, 478, 482, 485, 488, 491, 495, 498, 502, 505, 508, 512, 515, 519, 522, 526, 530, 533, 537, 
540, 544, 548, 552, 555, 559, 563, 567, 571, 574, 578, 582, 586, 590, 594, 598, 602, 607, 611, 615, 619, 623, 627, 632, 636, 640, 645, 649, 654, 658, 662, 667, 
672, 676, 681, 685, 690, 695, 699, 704, 709, 714, 719, 724, 728, 733, 738, 743, 749, 754, 759, 764, 769, 774, 780, 785, 790, 796, 801, 806, 812, 818, 823, 829, 
834, 840, 846, 851, 857, 863, 869, 875, 881, 887, 893, 899, 905, 911, 917, 924, 930, 936, 943, 949, 955, 962, 969, 975, 982, 988, 995, 1002, 1009, 1016, 1023  
};

#endif    // defined __TABLES_H
