#Victor Adair Najar A01226463

def largestSubstring(word):
    biggestSubIndex = 0
    totalLenght = 0
    actualLenght = 0
    lastIndex = 0
    knownLetters = []

    for i in range(0,len(word)):
        actualLetter = word[i]
        #print(actualLetter)
        for j in range(0,len(knownLetters)):
            if(actualLetter == knownLetters[j]):
                if(actualLenght > totalLenght):
                    biggestSubIndex = lastIndex
                    totalLenght = actualLenght
                    lastIndex = i
                    actualLenght = 0
                else:
                    actualLenght = 0
        #if(i == 0):
            #biggestSubIndex = i
            #totalLenght = actualLenght
        actualLenght += 1
        knownLetters.append(actualLetter)
    substring = ''
    for k in range(0,totalLenght):
        substring += knownLetters[biggestSubIndex+k]
    print('\'' + substring + '\'' + ' with lenght of ' + str(totalLenght))

#CHANGE THE STRING HERE!!!
largestSubstring('pwwkew')
