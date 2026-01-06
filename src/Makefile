CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall

SRC_DIR = solutions
BIN_DIR = bin
TEST_DIR = tests

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
EXECUTABLES = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.exe,$(SOURCES))

GEN_SRC = generator.cpp
GEN_BIN = generator.exe

all: $(EXECUTABLES) $(GEN_BIN)

$(BIN_DIR)/%.exe: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(GEN_BIN): $(GEN_SRC) utils/testlib.h
	$(CXX) $(CXXFLAGS) -o $@ $<

create_test_dir:
	mkdir -p $(TEST_DIR)

small: $(GEN_BIN) create_test_dir
	@COUNT=$${COUNT:-1}; \
	SEED=$$(date +%N); \
	echo "Generando $$COUNT casos pequeños..."; \
	for i in $$(seq 1 $$COUNT); do \
		CUR_SEED=$$((SEED + i)); \
		echo "  Generando prueba pequeña $$i/$$COUNT (seed: $$CUR_SEED)..."; \
		./$(GEN_BIN) small $$CUR_SEED > $(TEST_DIR)/test_small$$i.txt; \
	done; \
	echo "✓ $$COUNT casos pequeños generados en $(TEST_DIR)/"

medium: $(GEN_BIN) create_test_dir
	@COUNT=$${COUNT:-1}; \
	SEED=$$(date +%N); \
	echo "Generando $$COUNT casos medianos..."; \
	for i in $$(seq 1 $$COUNT); do \
		CUR_SEED=$$((SEED + i)); \
		echo "  Generando prueba mediana $$i/$$COUNT (seed: $$CUR_SEED)..."; \
		./$(GEN_BIN) medium $$CUR_SEED > $(TEST_DIR)/test_medium$$i.txt; \
	done; \
	echo "✓ $$COUNT casos medianos generados en $(TEST_DIR)/"

big: $(GEN_BIN) create_test_dir
	@COUNT=$${COUNT:-1}; \
	SEED=$$(date +%N); \
	echo "Generando $$COUNT casos grandes..."; \
	for i in $$(seq 1 $$COUNT); do \
		CUR_SEED=$$((SEED + i)); \
		echo "  Generando prueba grande $$i/$$COUNT (seed: $$CUR_SEED)..."; \
		./$(GEN_BIN) big $$CUR_SEED > $(TEST_DIR)/test_big$$i.txt; \
	done; \
	echo "✓ $$COUNT casos grandes generados en $(TEST_DIR)/"

fixed: $(GEN_BIN) create_test_dir
	@if [ -z "$(V)" ] || [ -z "$(K)" ]; then \
		echo "Uso: make fixed V=<valor> K=<valor>"; \
		echo "Ejemplo: make fixed V=5 K=3"; \
		exit 1; \
	fi; \
	SEED=$$(date +%N); \
	echo "Generando caso fijo V=$(V) K=$(K) (seed: $$SEED)..."; \
	./$(GEN_BIN) fixed $(V) $(K) $$SEED > $(TEST_DIR)/test_fixed_$(V)_$(K).txt; \
	echo "✓ Generado $(TEST_DIR)/test_fixed_$(V)_$(K).txt"

all_tests: $(GEN_BIN) create_test_dir
	@for size in small medium big; do \
		COUNT=$${COUNT:-1}; \
		SEED=$$(date +%N); \
		echo "Generando $$COUNT casos $$size..."; \
		for i in $$(seq 1 $$COUNT); do \
			CUR_SEED=$$((SEED + i)); \
			./$(GEN_BIN) $$size $$CUR_SEED > $(TEST_DIR)/test_$${size}$$i.txt; \
		done; \
	done; \
	echo "✓ Todos los casos de prueba generados en $(TEST_DIR)/"

clean:
	rm -rf $(BIN_DIR) $(TEST_DIR) $(GEN_BIN)
	@echo "Limpiado."

help:
	@echo "Targets disponibles:"
	@echo "  all                    - Compilar soluciones y generador (por defecto)"
	@echo "  small COUNT=n          - Generar n casos pequeños (por defecto: 1)"
	@echo "  medium COUNT=n         - Generar n casos medianos (por defecto: 1)"
	@echo "  big COUNT=n            - Generar n casos grandes (por defecto: 1)"
	@echo "  fixed V=n K=n          - Generar caso fijo con V y K específicos"
	@echo "  all_tests COUNT=n      - Generar n casos de cada tamaño"
	@echo "  clean                  - Remover ejecutables y archivos de prueba"
	@echo "  help                   - Mostrar esta ayuda"

.PHONY: all small medium big fixed all_tests clean help create_test_dir