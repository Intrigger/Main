struct strIntDictonary{
	char* key;
	int value;
};

struct strIntDictionaryVector{
	struct strIntDictonary element;
	struct strIntDictonaryVector* next;
};

int inVector(struct strIntDictionaryVector* vec, char* key, int vecSize){
	while (vecSize--){
		int len = strlen(key);

		int equals = 1;
		if (len != strlen(vec->element.key)) continue;
		for (int i = 0; i < len; i++){
			if (key[i] != vec->element.key[i]){
				equals = 0;
				break;
			}
		}
		if (equals == 1) return 1;

		vec = vec->next;
	}

	return 0;
}

int strEquals(char* str1, char* str2){
	if (strlen(str1) != strlen(str2)) return 0;

	for (int i = 0; i < strlen(str1); i++){
		if (str1[i] != str2[i]) return 0;
	}
	return 1;
}