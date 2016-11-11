/*
 * RSFS - Really Simple File System
 *
 * Copyright © 2010 Gustavo Maciel Dias Vieira
 * Copyright © 2010 Rodrigo Rocco Barbieri
 *
 * This file is part of RSFS.
 *
 * RSFS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Laboratório de Sistemas Operacionais
 * Prof. Gustavo Maciel Dias Vieira
 *
 * Projeto Final - Sistemas de Arquivos 
 *
 * Alunos:
 *  Igor Racca      RA: 511382
 *  Ingrid Maria Santos Pires RA: 620300
 *  Lucas da Rocha Pereira    RA: 379948
 *  Renato Candido Kurosaki   RA: 587834
 * ========================================================================== */

#include <stdio.h>
#include <string.h>

#include "disk.h"
#include "fs.h"

#define CLUSTERSIZE 4096

unsigned short fat[65536];

typedef struct {
       char used;
       char name[25];
       unsigned short first_block;
       int size;
} dir_entry;

dir_entry dir[128];

#define READ 0
#define WRITE 1
// le FAT e DIR caso flag = 0
// escreve FAT e DIR caso flag = 1
void readOrWrite_FatAndDir(int flag) {
  int i;
  char *buffer;

  if(flag == READ) {
    //Carrega FAT do disco
    buffer = (char *) fat;
    for (i = 0; i < 256; i++) {
      bl_read(i, &buffer[i * SECTORSIZE]);
    }
  
    //Carrega o Diretório do disco
    buffer = (char *) dir;
    for (i = 256; i < 264; i++) {
      bl_read(i, &buffer[(i-256) * SECTORSIZE]);
    }
  } else
  if(flag == WRITE) {
    //Escreve a FAT do disco
    buffer = (char *) fat;
    for (i = 0; i < 256; i++) {
      bl_write(i, &buffer[i * SECTORSIZE]);
    }
  
    //Escreve o Diretório do disco
    buffer = (char *) dir;
    for (i = 256; i < 264; i++) {
      bl_write(i, &buffer[(i-256) * SECTORSIZE]);
    }
  }
} 

int fs_init() {
  // Ler a FAT do disco para a memória e verificar formatação
  int i;

  readOrWrite_FatAndDir(READ);

  //Verificar se está formatado
  for(i=0;i<32;i++){
    if(fat[i]!=3){
      printf("O disco não está formatado!\n");
      fs_format();
    }
  }
  
  return 1;
}

int fs_format() {
  int i;
  
  // FAT
  for(i=0;i<32;i++){
    fat[i] = 3; // Inicializa o espaço da FAT
  }
    
  fat[i] = 4; // Inicializa o espaço do diretório
  
  for(i=33;i<65536;i++){
    fat[i] = 1; // Inicializa o espaço dos arquivos (espaço livre)
  }

  // Diretório
  for(i=0;i<128;i++){
    dir[i].used = '0';
  }

  readOrWrite_FatAndDir(WRITE);

  printf("Disco formatado com sucesso!\n");

  return 1;
}

int fs_free() {
  int i, cont = 0;

  for(i=33;i<65536;i++){
    if(fat[i] == 1)
      cont++;
  }
  //Numero de blocos livre * setor por bloco * tamanho do setor
  cont = cont * 8 * SECTORSIZE;

  return cont;
}

int fs_list(char *buffer, int size) {
  
  int i;
  strcpy(buffer, "");
  for (i = 0; i < 128; i++){ // percorre o diretório todo
    if (dir[i].used == '1'){
        buffer = buffer + sprintf(buffer,"%s\t\t%d\n", dir[i].name, dir[i].size); // add no buffer o nome do arquivo e seu tamanho
    }
  }

  return 1;
}

int fs_create(char* file_name) {
  int i;
  unsigned short int j;
  
  for(i=0;i<128;i++){
    if( strcmp(dir[i].name, file_name) == 0){
      printf("Arquivo já existente!\n");
      return 0;
    } 
  }
            
  for(i=0;i<128;i++){
    if(dir[i].used == '0'){
      dir[i].size = 0;
      strcpy(dir[i].name, file_name);
      dir[i].used = '1';
      
      for(j=33; j<65536; j++){
        if(fat[j] == 1){
          dir[i].first_block = j;
          fat[j] = 2;
          break;
        }
      }

      readOrWrite_FatAndDir(WRITE);
      
      return 1;
    }
  }
    
  
  return 0;
}

int fs_remove(char *file_name) {

  int i;
  unsigned short j,aux;

  for(i=0;i<128;i++){
    if( strcmp(dir[i].name, file_name) == 0 && dir[i].used != '0'){
      dir[i].used = '0';
      strcpy(dir[i].name,"");
      
      j = dir[i].first_block;
    
      do{
        aux = fat[j];
        fat[j] = 1;
        j = aux;
      }while(aux!=2);
      
      dir[i].first_block = 0;
      dir[i].size = -1;

      readOrWrite_FatAndDir(WRITE);
      
      return 1;
    } 
  }

  printf ("Arquivo não encontrado!\n");  
  return 0;
}

int fs_open(char *file_name, int mode) {
  printf("Função não implementada: fs_open\n");
  return -1;
}

int fs_close(int file)  {
  printf("Função não implementada: fs_close\n");
  return 0;
}

int fs_write(char *buffer, int size, int file) {
  printf("Função não implementada: fs_write\n");
  return -1;
}

int fs_read(char *buffer, int size, int file) {
  printf("Função não implementada: fs_read\n");
  return -1;
}
