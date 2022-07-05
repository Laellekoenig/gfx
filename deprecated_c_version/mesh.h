#ifndef MESH_H
#define MESH_H

#include <stdlib.h>

typedef struct {
    V4D v[3];
    Color c[3];
} HomoTri;

typedef struct VoidEntry VoidEntry;
struct VoidEntry {
    void* item;
    VoidEntry* next;
};

typedef struct {
    VoidEntry* head;
} VoidMesh;

void add2Mesh(VoidMesh* mesh, void* item) {
    VoidEntry* newEntry = malloc(sizeof(VoidEntry));
    newEntry->item = item;
    newEntry->next = NULL;

    if (mesh->head == NULL) {
        mesh->head = newEntry;
        return;
    }

    VoidEntry* current = mesh->head;
    while (current->next != NULL) current = current->next;
    current->next = newEntry;

}

void clearMesh(VoidMesh* mesh) {
    if (mesh->head == NULL) return;
    VoidEntry* prev = mesh->head;
    VoidEntry* curr = prev->next;
    free(prev->item);
    free(prev);

    while(curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev->item);
        free(prev);
    }
}

void matMulMesh(VoidMesh* mesh, Mat4D* mat) {
    VoidEntry* current = mesh->head;
    while(current != NULL) {
        HomoTri* currentTri = (HomoTri*) current->item;
        HomoTri multTri = {};
        memcpy(&multTri, currentTri, sizeof(HomoTri));

        for (int i = 0; i < 3; i++) {
            multMV4(mat, &currentTri->v[i], &multTri.v[i]);
        }
        *currentTri = multTri;
        current = current->next;
    }
}

#endif /* MESH_H */
