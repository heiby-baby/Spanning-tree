const bool ConnecCheck(bool* CM, int num_of_vertices) {                      //������� ��������� ���� �� ��������, ��� ���������� ��� ��������� ��������
                                                                            //�������� ����������� ���������� ������ � �������� � ��� ��������� O(n^3)
    bool* DM = new bool[num_of_vertices * num_of_vertices];

    for (int i = 0; i < num_of_vertices; i++) {                                      //���������� ������� ������������ �������� ���������
        for (int j = 0; j < num_of_vertices; j++) {
            if (i == j) {
                *(DM + i * num_of_vertices + j) = 1;
            }

            else {
                if (*(CM + i * num_of_vertices + j) == 0) {
                    *(DM + i * num_of_vertices + j) = 0;
                }
                else
                {
                    *(DM + i * num_of_vertices + j) = bool(*(CM + i * num_of_vertices + j));
                }
            }

        }
    }



    for (int k = 0; k < num_of_vertices; k++)  //������� ������� ������������ 
    {
        for (int i = 0; i < num_of_vertices; i++)
        {
            for (int j = 0; j < num_of_vertices; j++)
            {
                *(DM + i * num_of_vertices + j) = bool(bool(*(DM + i * num_of_vertices + j))) || \
                    (bool((*(DM + k * num_of_vertices + j))) && bool((*(DM + i * num_of_vertices + k))));
            }
        }
    }

    for (int i = 0; i < num_of_vertices; i++) {             //�������� ������� ������������ (���� ���� ���� 1 - "0", �� ���� �� �������)
        for (int j = 0; j < num_of_vertices; j++) {
            if (*(DM + i * num_of_vertices + j) == 0) {
                delete[] DM;
                delete[] CM;
                return false;
            }
        }
    }
    delete[] DM;
    delete[] CM;
    return true;

}