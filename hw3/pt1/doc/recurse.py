def recurse(An):
	Anw = 1/(3-An)
	if Anw == An:
		print(Anw)
		return
	else:
		recurse(Anw)

ia = 2
recurse(ia)
