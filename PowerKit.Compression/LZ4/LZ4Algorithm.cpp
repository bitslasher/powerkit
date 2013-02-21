// This is the main DLL file.

#include "stdafx.h"
#include "lz4.h"
#include "lz4hc.h"

using namespace System;

namespace PowerKit 
{ 
	namespace Compression 
	{
		public ref class LZ4Algorithm
		{
		private:
			int (*compress)(const char*, char*, int);

		public:
			LZ4Algorithm()
			{
				this->HighCompression = false;
			}

			LZ4Algorithm(bool highCompression)
			{
				this->HighCompression = highCompression;
			}

			property bool HighCompression
			{
				bool get()
				{
					return compress == LZ4_compressHC;
				}
				void set(bool value)
				{
					compress = value ? LZ4_compressHC : LZ4_compress;
				}
			}

			/// <summary>Compress a buffer.</summary>
			///
			int Compress(BYTEARRAY buffer, int offset, int length, BYTEARRAY outbuffer)
			{
				pin_ptr<unsigned char> in = &buffer[0];
				pin_ptr<unsigned char> out = &outbuffer[0];

				if (offset + length > buffer->Length)
					throw gcnew ArgumentException("Offset and/or Length parameters are invalid for the given input buffer size.");

				return compress((char*)in + offset, (char*)out, length);
			};

			//BYTEARRAY Compress(BYTEARRAY inbuffer, int inLength)
			//{
			//	BYTEARRAY output = gcnew array<unsigned char>(inLength * 2);
			//	int outputSize = Compress(inbuffer, inLength, output);
			//	Array::Resize(output, outputSize);
			//	return output;
			//};

			int Decompress(BYTEARRAY buffer, int offset, int length, BYTEARRAY outbuffer)
			{
				pin_ptr<unsigned char> in = &buffer[0];
				pin_ptr<unsigned char> out = &outbuffer[0];

				if (offset + length > buffer->Length)
					throw gcnew ArgumentException("Offset and/or Length parameters are invalid for the given input buffer size.");

				return LZ4_uncompress_unknownOutputSize((char*)in + offset, (char*)out, length, outbuffer->Length);
			}

			//BYTEARRAY Decompress(BYTEARRAY inbuffer, int inLength)
			//{
			//	int trueSize = (int)inbuffer[0];

			//	if (outbuffer->Length < trueSize)
			//		throw gcnew ArgumentException(String::Format("Output buffer must be at least {0} bytes in length.", trueSize));

			//	BYTEARRAY output = gcnew array<unsigned char>(inLength * 2);

			//}
		};
	}
}