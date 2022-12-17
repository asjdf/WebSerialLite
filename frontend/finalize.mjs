import { gzipAsync } from '@gfx/zopfli';
import { readFileSync, writeFileSync } from 'fs';
import { resolve } from 'path';


import path from 'path';
import {fileURLToPath} from 'url';
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

const SAVE_PATH = '../src';

const BUNDLE_JS = readFileSync(resolve(__dirname, './index.html'));

function chunkArray(myArray, chunk_size) {
    let index = 0;
    let arrayLength = myArray.length;
    let tempArray = [];
    for (index = 0; index < arrayLength; index += chunk_size) {
        let myChunk = myArray.slice(index, index + chunk_size);
        tempArray.push(myChunk);
    }
    return tempArray;
}

function addLineBreaks(buffer) {
    let data = '';
    let chunks = chunkArray(buffer, 30);
    chunks.forEach((chunk, index) => {
        data += chunk.join(',');
        if (index + 1 !== chunks.length) {
            data += ',\n';
        }
    });
    return data;
}

(async function(){
    try{
      const GZIPPED_INDEX = await gzipAsync(BUNDLE_JS, { numiterations: 15 });
  
      const FILE = 
`#ifndef _webserial_webapge_h
#define _webserial_webpage_h
const uint32_t WEBSERIAL_HTML_SIZE = ${GZIPPED_INDEX.length};
const uint8_t WEBSERIAL_HTML[] PROGMEM = { 
${ addLineBreaks(GZIPPED_INDEX) }
};
#endif
`;
  
      writeFileSync(resolve(__dirname, SAVE_PATH+'/WebSerialWebPage.h'), FILE);
      console.log(`[COMPRESS.js] Compressed Bundle into WebSerialWebPage.h header file | Total Size: ${(GZIPPED_INDEX.length / 1024).toFixed(2) }KB`)
    }catch(err){
      return console.error(err);
    }
  })();