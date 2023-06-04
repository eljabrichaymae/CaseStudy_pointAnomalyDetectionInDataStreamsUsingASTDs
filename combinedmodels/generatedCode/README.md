## Compilation

```console
$ mkdir build
$ cd build
$ cmake -S ../ -B .
$ make
```

## Execution

```console
$ ./COMBINEMODELS -i <path_to_trace> -1 <window_parameters> -2 <kde_parameters> -3 <kmeans_parameters> -4 <lof_parameters>
```
## Execution example

```console
$ ./COMBINEMODELS -i ../traces/astd3559trace.txt -1 ../inputs/window_parameters.json -2 0.0001 -3 2 -4 20
```

```plaintext
"bf84d575-2f75-4578-9d73-5f702235bad6"is malicious
"a84ff3a2-cfd4-4996-8bfe-9d5c744f27ca"is malicious
"60392d1b-2155-455e-9141-f19d124a21ec"is malicious
"4c788c05-8e1c-42b7-bc69-8ce1876d6e0e"is malicious
"57950dc6-af52-4658-b4d3-f52389bde68d"is malicious
"7420dc1f-4b65-48d2-8604-668f6b45cd44"is malicious
"793a8b56-e3a7-4ded-859e-12aa296c756b"is malicious
"4112360c-03b9-4c03-8594-e6d114713bc6"is malicious
"d9eb594b-9c9f-44d4-9802-fe0f71f096d9"is malicious
"d39db9cd-76a0-4d22-a989-a12446f475da"is malicious
"e4c54d8c-8859-4f35-9ed6-1dcc5890c6e8"is malicious
"108b00d8-03bd-4743-b1e1-b0f183c58f28"is malicious
"49dc3b5e-7c5d-48cb-bac5-1b0a97f8ead9"is malicious
"b1351636-2f37-4307-8a4f-c0d9c193ca33"is malicious
"0b4415ac-69f5-4def-bd92-27f4e87165b7"is malicious
"4415f004-ef25-4ba6-83ea-384dc4ece128"is malicious
"56f67fbf-d1dc-445c-a43d-b151af79e7c5"is malicious
"4d6510f0-3191-40b0-8dea-f79763070db4"is malicious
"2b4d3c41-b43d-4312-add4-b06f0369a890"is malicious
"0ab194df-e6fb-4c9c-908c-12e78a12f1e4"is malicious
"3863d5d3-4c91-412c-be7a-70be58fd7864"is malicious
"082674d1-8806-47c9-936e-40d2c8c3b05a"is malicious
number of alerts :  22
```