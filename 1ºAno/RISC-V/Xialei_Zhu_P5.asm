/*---------------------------------------------------------------------
**
**  Fichero:
**    fun_asm.asm  01/05/2025
**
**    (c) J.M. Mendias
**    Fundamentos de Computadores II
**    Facultad de Informática. Universidad Complutense de Madrid
**
**  Propósito:
**    Fichero de código para la práctica 5
**
**-------------------------------------------------------------------*/
.text
.global matrixCopy
.global matrixMul
.global matrixPow

// Función: matrixCopy(int n, int x[n][n], int z[n][n])
// Argumentos: a0 = n, a1 = x (origen), a2 = z (destino)

matrixCopy:
    li t0, 0                  // i = 0
copy_loop_i:
    bge t0, a0, copy_end      // Si i >= n, fin de la copia
    li t1, 0                  // j = 0
copy_loop_j:
    bge t1, a0, copy_next_i   // Si j >= n, pasa a la siguiente fila

    // Calcular dirección: dir = base + (i * n + j) * 4
    mul t2, t0, a0            // t2 = i * n
    add t2, t2, t1            // t2 = i * n + j
    slli t2, t2, 2            // t2 = (i * n + j) * 4 (offset en bytes)

    add t3, a1, t2            // t3 = dirección de x[i][j]
    add t4, a2, t2            // t4 = dirección de z[i][j]

    lw t5, 0(t3)              // t5 = x[i][j]
    sw t5, 0(t4)              // z[i][j] = t5

    addi t1, t1, 1            // j++
    j copy_loop_j
copy_next_i:
    addi t0, t0, 1            // i++
    j copy_loop_i
copy_end:
    ret


// Función: matrixMul(int n, int x[n][n], int y[n][n], int z[n][n])
// Argumentos: a0=n, a1=x, a2=y, a3=z

matrixMul:
    li t0, 0                  // i = 0
mul_loop_i:
    bge t0, a0, mul_end       // Si i >= n, fin
    li t1, 0                  // j = 0
mul_loop_j:
    bge t1, a0, mul_next_i    // Si j >= n, siguiente fila i

    li t4, 0                  // accum = 0 (guardará el resultado de z[i][j])
    li t2, 0                  // k = 0
mul_loop_k:
    bge t2, a0, mul_next_j    // Si k >= n, terminamos la celda

    // Leer x[i][k] -> offset = (i * n + k) * 4
    mul t5, t0, a0            // t5 = i * n
    add t5, t5, t2            // t5 = i * n + k
    slli t5, t5, 2            // t5 = (i*n + k) * 4
    add t5, a1, t5            // t5 = dir x[i][k]
    lw t6, 0(t5)              // t6 = x[i][k]

    // Leer y[k][j] -> offset = (k * n + j) * 4
    mul t5, t2, a0            // t5 = k * n
    add t5, t5, t1            // t5 = k * n + j
    slli t5, t5, 2            // t5 = (k*n + j) * 4
    add t5, a2, t5            // t5 = dir y[k][j]
    lw t3, 0(t5)              // t3 = y[k][j]

    // Multiplicar y acumular
    mul t5, t6, t3            // t5 = x[i][k] * y[k][j]
    add t4, t4, t5            // accum += t5

    addi t2, t2, 1            // k++
    j mul_loop_k
mul_next_j:
    // Guardar el resultado en z[i][j] -> offset = (i * n + j) * 4
    mul t5, t0, a0            // t5 = i * n
    add t5, t5, t1            // t5 = i * n + j
    slli t5, t5, 2            // t5 = (i*n + j)*4
    add t5, a3, t5            // t5 = dir z[i][j]
    sw t4, 0(t5)              // z[i][j] = accum

    addi t1, t1, 1            // j++
    j mul_loop_j
mul_next_i:
    addi t0, t0, 1            // i++
    j mul_loop_i
mul_end:
    ret


// Función: matrixPow(int n, int x[n][n], int e, int z[n][n])
// Argumentos: a0=n, a1=x, a2=e, a3=z
matrixPow:
    // PRÓLOGO
    addi sp, sp, -24          // Espacio para registros salvados
    sw ra, 20(sp)
    sw s0, 16(sp)             // s0 = n
    sw s1, 12(sp)             // s1 = x
    sw s2, 8(sp)              // s2 = e
    sw s3, 4(sp)              // s3 = z
    sw s4, 0(sp)              // s4 = i (contador del bucle pow)

    mv s0, a0
    mv s1, a1
    mv s2, a2
    mv s3, a3

    // RESERVA DE VARIABLE LOCAL (aux[n][n])
    mul t0, s0, s0            // t0 = n * n (número total de celdas)
    slli t0, t0, 2            // t0 = n * n * 4 bytes de tamaño total
    sub sp, sp, t0            // El stack pointer baja. Creamos aux en la pila

    // INICIALIZAR z COMO MATRIZ IDENTIDAD
    li t0, 0                  // j = 0
init_j:
    bge t0, s0, pow_start     // Si j >= n, a calcular la potencia
    li t1, 0                  // k = 0
init_k:
    bge t1, s0, init_next_j

    // Dir z[j][k] = z + (j*n + k)*4
    mul t2, t0, s0
    add t2, t2, t1
    slli t2, t2, 2
    add t2, s3, t2

    beq t0, t1, is_diag       // Si j == k, es la diagonal
    li t3, 0                  // No es diagonal: valor 0
    j store_z
is_diag:
    li t3, 1                  // Es diagonal: valor 1
store_z:
    sw t3, 0(t2)

    addi t1, t1, 1            // k++
    j init_k
init_next_j:
    addi t0, t0, 1            // j++
    j init_j

    // BUCLE DE POTENCIAS
pow_start:
    li s4, 1                  // i = 1
pow_loop:
    bgt s4, s2, pow_end       // if (i > e) salir del bucle

    // Llamada: matrixMul(n, x, z, aux)
    mv a0, s0                 // a0 = n
    mv a1, s1                 // a1 = x
    mv a2, s3                 // a2 = z
    mv a3, sp                 // a3 = aux (su dirección es exactamente sp)
    call matrixMul

    // Llamada: matrixCopy(n, aux, z)
    mv a0, s0                 // a0 = n
    mv a1, sp                 // a1 = aux
    mv a2, s3                 // a2 = z
    call matrixCopy

    addi s4, s4, 1            // i++
    j pow_loop

pow_end:
    // EPÍLOGO Y LIBERACIÓN DE MEMORIA
    mul t0, s0, s0
    slli t0, t0, 2
    add sp, sp, t0            // Liberamos la matriz aux de la pila

    lw s4, 0(sp)              // Restauramos registros salvados
    lw s3, 4(sp)
    lw s2, 8(sp)
    lw s1, 12(sp)
    lw s0, 16(sp)
    lw ra, 20(sp)
    addi sp, sp, 24           // Liberamos el marco original
    ret
