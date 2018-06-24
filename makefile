compile: 
	@echo "run $@ command"
	@g++ -std=c++11 ./src/translator/**.cc ./src/**.cc -I./src -I./src/translator -o ./bin/qualis

run:
	@echo "run $@ command"
	@make compile && ./bin/qualis
