from PIL import Image
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--file', '-f', required = True, help = 'Image file to convert')

args = vars(parser.parse_args())

file_name = args.get('file')

if file_name.endswith('.png') is False:
	raise ValueError('This script only works with .png file!')

with Image.open(file_name) as img:
	result_name = file_name[:-4]
	result = img.convert('RGB')

result.save(result_name + '.jpg')
