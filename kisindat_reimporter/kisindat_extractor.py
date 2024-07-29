#credits: Mumm-Ra 2023-11-19. 
#PSX PANZER BANDIT KASINDAT REBUILDER
from ast import mod
import sys, struct, os, traceback
from ctypes import pointer


def get_kisin_info(exe_file, kisin_info_offset):
    dados = []

    with open(exe_file, 'rb') as arquivo:
        arquivo.seek(kisin_info_offset)

        file_count = 332
        i = 0
        while i < file_count:
            #print("aqui2")
            ptr_offset = arquivo.tell()
            string_dados = arquivo.read(16)
            if not string_dados:
                break  # Sai do loop se não houver mais dados
            
            offset = struct.unpack('<I', arquivo.read(4))[0]
            size = struct.unpack('<I', arquivo.read(4))[0]

            if size > 0:
                dados.append((ptr_offset, offset, size,string_dados.decode('utf-8')))
            i = i + 1
    return dados

def export_files(kisin_info, arquivo_entrada, output_dir):
    os.makedirs(output_dir, exist_ok=True)

    for ptr_offset, offset, size, string_dados in kisin_info:
        try:
            with open(arquivo_entrada, 'rb') as arquivo:
                arquivo.seek(offset)
                dados = arquivo.read(size)
                nome_arquivo_saida = output_dir + '\\' + string_dados.replace('\0', '')
                with open(nome_arquivo_saida, 'wb') as arquivo_saida:
                    arquivo_saida.write(dados)
                #print(f'Dados extraídos de {arquivo_entrada} com offset {offset}, tamanho {size}. Salvo em {nome_arquivo_saida}')
        except Exception as e:
            print(f'Erro ao exportar arquivo {string_dados}: {str(e)}') 

def reimport_files(kisin_info, kisin_orig, kisin_new, exe_orig, exe_new, output_dir):
    
    with open(exe_orig, 'rb') as exe_origfile:
        exe_data = exe_origfile.read()

    with open(exe_new, 'wb') as exe_newfile:
        exe_newfile.write(exe_data)

        with open(kisin_new, 'wb') as kisin_newfile:
            kisin_header_size = 4096
            
            with open(kisin_orig, 'rb') as kisin_origfile:
                header_orig = kisin_origfile.read(kisin_header_size)
                kisin_newfile.write(header_orig)
                curr_write_ofs = kisin_header_size

            for ptr_offset, offset, size, string_dados in kisin_info:
                try:
                    kisin_newfile.seek(curr_write_ofs)
                    exe_newfile.seek(ptr_offset+ 0x10)
                    current_fname = output_dir + '\\' + string_dados.replace('\0',"")
                    
                    with open(current_fname, 'rb') as container_filenew:
                        dados = container_filenew.read()
                        new_size = container_filenew.tell()

                        kisin_newfile.write(dados)
                        exe_newfile.write(struct.pack('<I', curr_write_ofs))
                        exe_newfile.write(struct.pack('<I', new_size))
                        
                        add_bytes = 0
                        if (new_size % 0x800) > 0:
                            add_bytes = 0x800 - (new_size % 0x800)
                        
                        mod_size = new_size + add_bytes
                        curr_write_ofs = curr_write_ofs + mod_size

                except Exception as e:
                    print(f'Erro ao reimportar arquivo {string_dados}: {str(e)}')
                    traceback.print_exc()
                    

def write_kisin_info(nome_arquivo_saida, kisin_info):
    with open(nome_arquivo_saida, 'wb') as arquivo_saida:
        for ptr_offset, offset, size, string_dados in kisin_info:
            dados_empacotados = struct.pack(f'<{len(string_dados)}sIII', string_dados.encode('utf-8'),ptr_offset,offset, size)
            arquivo_saida.write(dados_empacotados)

if __name__ == "__main__":

    if len(sys.argv) != 5:
        print("Uso: python kisindat_extractor <mode> <slps_name> <kisindat_name> ")
        print("operation mode: e (extract) or r (reimport)")
        sys.exit(1)

    op_mode = sys.argv[1]
    exe_file = sys.argv[2]
    container_name = sys.argv[3]
    output_dir = sys.argv[4]

    # Change script generation parameters here
    kisin_info_offset = 0x7242C

    kisin_info = get_kisin_info(exe_file, kisin_info_offset)

    for ptr_offset, offset, size, string_dados in kisin_info:
        print(f'String: {string_dados}, Offset: {offset}, Size: {size}')

    write_kisin_info("ksindat_info.bin", kisin_info)

    if op_mode == 'e':
        export_files(kisin_info, container_name, output_dir)
    elif op_mode == 'r':
        reimport_files(kisin_info, container_name, container_name + '.new', exe_file, exe_file + '.new', output_dir)
    else:
        print("Invalid mode: " + op_mode)
        sys.exit(1)

    #pointers_table_end = 0X3a24     #
    #offset_strings = 0x00               #<0x81><0x40>Shocking

    
    #armips_script = generate_armips_script(kisin_info,binary_file2)
    #if armips_script:
    #    with open("output_script.asm", "w") as output_file:
    #        output_file.write(armips_script)
    #    print("Script sucessfully generated (output_script.asm).")
    
