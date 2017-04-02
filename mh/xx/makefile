FILE=电龙
FORMAT=png
OUT=$(FILE).$(FORMAT)


run:
	dot -T$(FORMAT) -O ${FILE}
	open $(OUT)

clean:
	rm *.${FORMAT}
