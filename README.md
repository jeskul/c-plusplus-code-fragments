# C++ Code Fragments

This repository contains code fragments. It is not inteneded to be a library or finished application of any sort. Just bits of code that I find useful.

## Contents
* Message Queue - example on how you can do message based inter thread communication in C++. Todo: add move semantics
* Oneshot Timer - Useful timer class that makes use of the Message Queue.

## Example
See main.cpp

## Unit Tests
Tests are located in /test
They use Google tests

## Build
E.g. Create a sub folder named build_ut
Go into that folder
Type cmake ..
make
make test

etc