Imports System
Imports System.IO
Imports System.Text

Public Class Form1
    Dim MyFiles() As String
    Dim cubeDimension As Integer
    Dim DragDropPerformed As Boolean
    Dim executeFileName As String
    Dim sr As StreamReader


    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        hide3by3()
        hide4by4()
        hide5by5()
        DragDropPerformed = False

    End Sub

    Private Sub Button2_Click(ByVal sender As Object,
        ByVal e As System.EventArgs) Handles Button2.Click
        Dim inputFile As String = ""
        If DragDropPerformed = False Then
            If OpenFileDialog1.ShowDialog = DialogResult.OK Then
                inputFile = OpenFileDialog1.FileName
                sr = New StreamReader(inputFile)
                Label229.Text = inputFile
            End If
        ElseIf DragDropPerformed = True Then
            inputFile = MyFiles(0)
            sr = New StreamReader(inputFile)
        End If

        cubeDimension = sr.ReadLine()
        Dim executeFileName As String
        If cubeDimension = 3 Then
            executeFileName = "CubeSolverENG3.exe"
        ElseIf cubeDimension = 4 Then
            executeFileName = "CubeSolverENG4.exe"
        ElseIf cubeDimension = 5 Then
            executeFileName = "CubeSolverENG5.exe"
        Else
            OpenFileDialog1.ShowDialog()
            End
        End If

        Dim psi As New System.Diagnostics.ProcessStartInfo(executeFileName)

        psi.Arguments = String.Format("1 {1}{0}{1}", (inputFile), Chr(34))
        psi.RedirectStandardOutput = True
        psi.WindowStyle = ProcessWindowStyle.Hidden
        psi.UseShellExecute = False
        Dim listFiles As System.Diagnostics.Process
        listFiles = System.Diagnostics.Process.Start(psi)
        Dim myOutput As System.IO.StreamReader = listFiles.StandardOutput

        Dim pieceIndexes(100, 100) As Integer



        Dim allLabels3by3() As Label = New Label() {Label1, Label2, Label3, Label4, Label5, Label6, Label7, Label8, Label9,
                                                    Label10, Label11, Label12, Label13, Label14, Label15, Label16, Label17,
                                                    Label18, Label19, Label20, Label21, Label22, Label23, Label24,
                                                    Label25, Label26, Label27}

        Dim allLabels4by4() As Label = New Label() {Label31, Label32, Label33, Label34, Label35, Label36, Label37, Label38,
                                                    Label39, Label40, Label41, Label42, Label43, Label44, Label45, Label46,
                                                    Label47, Label48, Label49, Label50, Label51, Label52, Label53, Label54,
                                                    Label55, Label56, Label57, Label58, Label59, Label60, Label61, Label62,
                                                    Label63, Label64, Label65, Label66, Label67, Label68, Label69, Label70,
                                                    Label71, Label72, Label73, Label74, Label75, Label76, Label77, Label78,
                                                    Label79, Label80, Label81, Label82, Label83, Label84, Label85, Label86,
                                                    Label87, Label88, Label89, Label90, Label91, Label92, Label93, Label94}

        Dim allLabels5by5() As Label = New Label() {Label95, Label96, Label97, Label98, Label99, Label100, Label101, Label102,
                                                    Label103, Label104, Label105, Label106, Label107, Label108, Label109, Label110,
                                                    Label111, Label112, Label113, Label114, Label115, Label116, Label117, Label118,
                                                    Label119, Label120, Label121, Label122, Label123, Label124, Label125, Label126,
                                                    Label127, Label128, Label129, Label130, Label131, Label132, Label133, Label134,
                                                    Label135, Label136, Label137, Label138, Label139, Label140, Label141, Label142,
                                                    Label143, Label144, Label145, Label146, Label147, Label148, Label149, Label150,
                                                    Label151, Label152, Label153, Label154, Label155, Label156, Label157, Label158,
                                                    Label159, Label160, Label161, Label162, Label163, Label164, Label165, Label166,
                                                    Label167, Label168, Label169, Label170, Label171, Label172, Label173, Label174,
                                                    Label175, Label176, Label177, Label178, Label179, Label180, Label181, Label182,
                                                    Label183, Label184, Label185, Label186, Label187, Label188, Label189, Label190,
                                                    Label191, Label192, Label193, Label194, Label195, Label196, Label197, Label198,
                                                    Label199, Label200, Label201, Label202, Label203, Label204, Label205, Label206,
                                                    Label207, Label208, Label209, Label210, Label211, Label212, Label213, Label214,
                                                    Label215, Label216, Label217, Label218, Label219}

        Dim allColors() As Color = New Color() {Color.Red, Color.Blue, Color.Black, Color.Green, Color.Indigo, Color.Orange, Color.Purple, Color.Cyan, Color.LightBlue,
                                                    Color.Gold, Color.GreenYellow, Color.Moccasin, Color.Navy, Color.DarkOliveGreen, Color.DimGray, Color.DeepPink, Color.DarkViolet,
                                                    Color.DarkSlateBlue, Color.OrangeRed, Color.PaleGreen, Color.Plum, Color.Salmon, Color.Tan, Color.SteelBlue, Color.Tomato, Color.Olive}


        myOutput.ReadLine()
        setupBoard(cubeDimension)

        Dim numPieces As Integer = myOutput.ReadLine
        Dim pieceSize(numPieces) As Integer
        Dim pieceId(numPieces) As Integer

        Dim textBoxString As String
        textBoxString = "NUM Of PIECES:   "
        textBoxString += numPieces.ToString
        textBoxString += vbNewLine

        For pieceNum As Integer = 0 To numPieces - 1
            pieceId(pieceNum) = myOutput.ReadLine
            pieceSize(pieceNum) = myOutput.ReadLine
            textBoxString += "ID:"
            textBoxString += (pieceId(pieceNum)).ToString
            textBoxString += " SIZE:"
            textBoxString += (pieceSize(pieceNum)).ToString
            textBoxString += vbNewLine

            For pieceIndex As Integer = 0 To pieceSize(pieceNum) - 1
                pieceIndexes(pieceNum, pieceIndex) = myOutput.ReadLine
                textBoxString += (pieceIndexes(pieceNum, pieceIndex)).ToString
                textBoxString += vbNewLine
                If cubeDimension = 3 Then
                    allLabels3by3(pieceIndexes(pieceNum, pieceIndex)).BackColor = allColors(pieceNum)
                    allLabels3by3(pieceIndexes(pieceNum, pieceIndex)).Text = pieceId(pieceNum)
                ElseIf cubeDimension = 4 Then
                    allLabels4by4(pieceIndexes(pieceNum, pieceIndex)).BackColor = allColors(pieceNum)
                    allLabels4by4(pieceIndexes(pieceNum, pieceIndex)).Text = pieceId(pieceNum)
                ElseIf cubeDimension = 5 Then
                    allLabels5by5(pieceIndexes(pieceNum, pieceIndex)).BackColor = allColors(pieceNum)
                    allLabels5by5(pieceIndexes(pieceNum, pieceIndex)).Text = pieceId(pieceNum)

                End If

            Next

        Next
        TextBox1.Text = textBoxString
        listFiles.WaitForExit(2000)
        If listFiles.HasExited Then
            Dim output As String = myOutput.ReadToEnd
            Debug.WriteLine(output)


        End If
        DragDropPerformed = False
    End Sub

    Private Sub setupBoard(size As String)
        If size = "3" Then
            hide4by4()
            hide5by5()
            show3by3()
        ElseIf size = "4" Then
            hide3by3()
            hide5by5()
            show4by4()
        ElseIf size = "5" Then
            hide3by3()
            hide4by4()
            show5by5()
        End If

    End Sub
    Private Sub hide3by3()
        Label28.Hide()
        Label29.Hide()
        Label30.Hide()
        TableLayoutPanel1.Hide()
        TableLayoutPanel2.Hide()
        TableLayoutPanel3.Hide()
    End Sub
    Private Sub show3by3()
        Label28.Show()
        Label29.Show()
        Label30.Show()
        TableLayoutPanel1.Show()
        TableLayoutPanel2.Show()
        TableLayoutPanel3.Show()

    End Sub

    Private Sub hide4by4()
        Label220.Hide()
        Label221.Hide()
        Label222.Hide()
        Label223.Hide()
        TableLayoutPanel4.Hide()
        TableLayoutPanel5.Hide()
        TableLayoutPanel6.Hide()
        TableLayoutPanel7.Hide()
    End Sub
    Private Sub show4by4()
        Label220.Show()
        Label221.Show()
        Label222.Show()
        Label223.Show()
        TableLayoutPanel4.Show()
        TableLayoutPanel5.Show()
        TableLayoutPanel6.Show()
        TableLayoutPanel7.Show()
    End Sub
    Private Sub hide5by5()
        Label224.Hide()
        Label225.Hide()
        Label226.Hide()
        Label227.Hide()
        Label228.Hide()
        TableLayoutPanel8.Hide()
        TableLayoutPanel9.Hide()
        TableLayoutPanel10.Hide()
        TableLayoutPanel11.Hide()
        TableLayoutPanel12.Hide()


    End Sub
    Private Sub show5by5()
        Label224.Show()
        Label225.Show()
        Label226.Show()
        Label227.Show()
        Label228.Show()
        TableLayoutPanel8.Show()
        TableLayoutPanel9.Show()
        TableLayoutPanel10.Show()
        TableLayoutPanel11.Show()
        TableLayoutPanel12.Show()

    End Sub

    Private Sub GroupBox1_Enter(sender As Object, e As EventArgs)

    End Sub

    Private Sub ListBox1_DragEnter(ByVal sender As Object, ByVal e As _
    System.Windows.Forms.DragEventArgs) Handles ListBox1.DragEnter
        If e.Data.GetDataPresent(DataFormats.FileDrop) Then
            e.Effect = DragDropEffects.All
        End If
    End Sub

    Private Sub ListBox1_DragDrop(ByVal sender As Object, ByVal e As _
    System.Windows.Forms.DragEventArgs) Handles ListBox1.DragDrop
        hide3by3()
        hide4by4()
        hide5by5()
        If e.Data.GetDataPresent(DataFormats.FileDrop) Then
            'Dim MyFiles() As String
            Dim i As Integer

            ' Assign the files to an array.
            MyFiles = e.Data.GetData(DataFormats.FileDrop)
            ' Loop through the array and add the files to the list.
            For i = 0 To MyFiles.Length - 1
                ListBox1.Items.Add(MyFiles(i))
                TextBox1.Text = ListBox1.Items.ToString
            Next
        End If
        DragDropPerformed = True
        Button2.PerformClick()
    End Sub



End Class
