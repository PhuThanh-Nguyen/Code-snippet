from PyPDF2 import PdfFileMerger
import os

L = []
outputName = 'output.pdf'

for fileName in os.listdir():
	if fileName.endswith('.pdf') and fileName != outputName:
		L.append(fileName)

merger = PdfFileMerger()

merger.setPageLayout('/SinglePage')

for fileName in L:
	merger.append(fileName)

merger.write(outputName)
merger.close()
