SHELL := /usr/bin/env bash
MAKEFLAGS += --silent

$(shell if [ ! -f .env ] && [ -f .example.env ]; then cp .example.env .env; fi)
-include .env
export

# make help: @ List available tasks on this project
help:
	grep -h -E '[a-zA-Z0-9\.\-]+:.*?@ .*$$' $(MAKEFILE_LIST) | tr -d '#' | awk 'BEGIN {FS = ":.*?@ "}; {printf "\033[36m%-40s\033[0m %s\n", $$1, $$2}'

.PHONY: help install clean format lint scan test pre-commit

define install
	if ! type poetry >/dev/null; then curl -sSL https://install.python-poetry.org | python3 -; fi

	poetry config virtualenvs.in-project true
	poetry config virtualenvs.prefer-active-python true
	poetry env use $(shell python3 --version | sed 's/[^[0-9\.]]*//g')

	if ! poetry lock --check 2>/dev/null; then poetry lock --no-update; fi

	poetry install

	poetry run pre-commit install
	poetry run pre-commit autoupdate
endef

.venv:
	$(call install)

# make install: @ Install dependencies
install:
	$(call install)

# poetry add [--group dev|...] ...@latest: @ Add / update to latest [dev|... group] dependencies

# poetry remove [--group dev|...] ...: @ Remove [dev|... group] dependencies

# make clean: @ Remove cache, checkpoints, coverage, etc.
clean:
	find . -type f -name *.DS_Store -ls -delete
	find . | grep -E '(__pycache__|\.pyc|\.pyo)' | xargs rm -rf
	find . | grep -E .mypy_cache | xargs rm -rf
	find . | grep -E .pytest_cache | xargs rm -rf
	find . | grep -E .ipynb_checkpoints | xargs rm -rf
	find . | grep -E .trash | xargs rm -rf
	rm -f .coverage
	find . -type f -name main -not -path "./.git/*" -ls -delete
	find . -type f -name test -not -path "./.git/*" -ls -delete
	find . -type f -name *.class -not -path "./.git/*" -ls -delete

# make format: @ Format code
format: .venv
	go fmt ./...
	poetry run isort .
	poetry run black .

# make lint: @ Lint code and type hints
lint: .venv
	cppcheck . -i .venv
	go vet ./...
	poetry run flake8
	poetry run mypy .
	poetry run refurb .

# make scan: @ Scan code and dependencies for security vulnerabilities
scan: .venv
	poetry run bandit -c pyproject.toml -r .
	poetry run safety check

SUBDIRS := $(shell find ./ -type d -name "*" -not -path "./.git/*" -not -path "*/.*")
SUBDIRS := $(subst ./,,$(SUBDIRS))

.PHONY: $(SUBDIRS)

# make test: @ Run tests
test: .venv
	go test ./...
	for dir in $(SUBDIRS); do \
		if ls $$dir | grep -q "Makefile"; then \
			echo -e "\n$$dir"; \
			$(MAKE) -C $$dir test || exit 1 ; \
		fi; \
	done
	poetry run pytest -vv

# make pre-commit: @ Run pre-commit checks
pre-commit: .venv
	./.git/hooks/pre-commit
