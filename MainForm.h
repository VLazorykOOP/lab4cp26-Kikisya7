#pragma once

namespace ComputerShop {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			LoadData(); // загрузка данных при старте формы
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBoxName;
	private: System::Windows::Forms::TextBox^ textBoxCPU;
	private: System::Windows::Forms::TextBox^ textBoxFreq;
	private: System::Windows::Forms::TextBox^ textBoxVideo;
	private: System::Windows::Forms::TextBox^ textBoxCD;
	private: System::Windows::Forms::TextBox^ textBoxSound;
	private: System::Windows::Forms::TextBox^ textBoxHDD;
	private: System::Windows::Forms::Button^ buttonAdd;
	private: System::Windows::Forms::DataGridView^ dataGridView1;

	private:
		System::ComponentModel::Container^ components;

		// строка подключения к LocalDB
		String^ connStr = "Data Source=(LocalDB)\\MSSQLLocalDB;Initial Catalog=ComputerDB;Integrated Security=True";

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBoxName = (gcnew System::Windows::Forms::TextBox());
			this->textBoxCPU = (gcnew System::Windows::Forms::TextBox());
			this->textBoxFreq = (gcnew System::Windows::Forms::TextBox());
			this->textBoxVideo = (gcnew System::Windows::Forms::TextBox());
			this->textBoxCD = (gcnew System::Windows::Forms::TextBox());
			this->textBoxSound = (gcnew System::Windows::Forms::TextBox());
			this->textBoxHDD = (gcnew System::Windows::Forms::TextBox());
			this->buttonAdd = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->SuspendLayout();

			// labels
			array<String^>^ labels = {
				"Название компьютера","Тип процессора","Тактовая частота",
				"Видеокарта","CDROM / CDRW","Звуковая карта","Объём винчестера"
			};

			array<TextBox^>^ boxes = gcnew array<TextBox^>(7);
			for (int i = 0; i < 7; i++)
			{
				Label^ lbl = gcnew Label();
				lbl->Text = labels[i];
				lbl->Location = Point(30, 30 + i * 50);
				lbl->AutoSize = true;
				this->Controls->Add(lbl);

				TextBox^ tb = gcnew TextBox();
				tb->Location = Point(250, 30 + i * 50);
				tb->Width = 150;
				this->Controls->Add(tb);
				boxes[i] = tb;
			}

			textBoxName = boxes[0];
			textBoxCPU = boxes[1];
			textBoxFreq = boxes[2];
			textBoxVideo = boxes[3];
			textBoxCD = boxes[4];
			textBoxSound = boxes[5];
			textBoxHDD = boxes[6];

			// кнопка добавить
			buttonAdd->Text = "Добавить";
			buttonAdd->Location = Point(250, 400);
			buttonAdd->Click += gcnew EventHandler(this, &MainForm::buttonAdd_Click);
			this->Controls->Add(buttonAdd);

			// DataGridView
			dataGridView1->Location = Point(450, 30);
			dataGridView1->Size = Drawing::Size(400, 350);
			this->Controls->Add(dataGridView1);

			// MainForm
			this->Text = "Продажа компьютеров";
			this->Size = Drawing::Size(900, 500);
			this->StartPosition = FormStartPosition::CenterScreen;

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

	private:
		void LoadData()
		{
			try
			{
				SqlConnection^ con = gcnew SqlConnection(connStr);
				con->Open();
				SqlDataAdapter^ da = gcnew SqlDataAdapter("SELECT * FROM Computers", con);
				DataTable^ dt = gcnew DataTable();
				da->Fill(dt);
				dataGridView1->DataSource = dt;
				con->Close();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Ошибка загрузки данных: " + ex->Message);
			}
		}

	private: System::Void buttonAdd_Click(System::Object^ sender, System::EventArgs^ e)
	{
		try
		{
			SqlConnection^ con = gcnew SqlConnection(connStr);
			con->Open();

			String^ sql = "INSERT INTO Computers (NamePC, CpuType, CpuFreq, Video, CDROM, Sound, HDD) VALUES (N'" +
				textBoxName->Text + "', N'" +
				textBoxCPU->Text + "', N'" +
				textBoxFreq->Text + "', N'" +
				textBoxVideo->Text + "', N'" +
				textBoxCD->Text + "', N'" +
				textBoxSound->Text + "', N'" +
				textBoxHDD->Text + "')";

			SqlCommand^ cmd = gcnew SqlCommand(sql, con);
			cmd->ExecuteNonQuery();
			con->Close();

			MessageBox::Show("Компьютер добавлен!");
			LoadData();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Ошибка базы данных: " + ex->Message);
		}
	}
	};
}
