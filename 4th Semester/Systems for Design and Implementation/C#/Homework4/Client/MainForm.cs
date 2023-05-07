using OnwardTravel.Models;
using OnwardTravel.Services.Exceptions;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Windows.Forms;

namespace OnwardTravel.Client
{
    internal partial class MainForm : Form
    {
        private Form _parent;
        private ClientController _ctrl;
        private Ride selectedRide = null;

        public MainForm()
        {
            InitializeComponent();
            designTable(ridesTable);
            designTable(clientsTable);
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            _ctrl.Logout();
            _ctrl.UpdateEvent -= UserUpdate;
        }

        private void designTable(DataGridView table)
        {
            table.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            table.MultiSelect = false;
            table.ReadOnly = true;
            table.AllowUserToResizeRows = false;
            table.AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
            table.RowHeadersVisible = false;
        }

        public void UserUpdate(object sender, ClientEventArgs ev)
        {
            if (ev.UserEventType == UserEvent.RESERVATION_CREATED)
            {
                ridesTable.BeginInvoke(new RefreshRidesDelegate(RefreshRides));
                clientsTable.BeginInvoke(new RefreshReservationDelegate(RefreshReservations));
            }
        }

        // delegate to be called back by the GUI 
        public delegate void RefreshReservationDelegate();
        public delegate void RefreshRidesDelegate();
        
        // method for update
        public void RefreshReservations()
        {
            refreshClients(_ctrl.FindReservationsByRide(selectedRide));
        }

        public void RefreshRides()
        {
            refreshRides(_ctrl.FindAllRides());
        }

        public void SetParent(Form parent)
        {
            _parent = parent;
        }

        public void SetController(ClientController ctrl)
        {
            _ctrl = ctrl;
            _ctrl.UpdateEvent += UserUpdate;
            refreshRides(_ctrl.FindAllRides());
            welcomeLabel.Text = $"Welcome, {_ctrl.CurrentUser.Username}!";
        }

        public void refreshRides(IList<Ride> rides)
        {
            ridesTable.DataSource = rides.Select(ride => new { 
                Destination = ride.Destination, 
                Departure = ride.Departure,
                AvailableSeats = _ctrl.FindEmptySeatsOnRide(ride) }).ToList();
        }

        public void refreshClients(ClientSeat[] clients)
        {
            clientsTable.DataSource = clients.Select(client => new { Seat = client.ReservedSeat.SeatNumber, Client = client.Client == null ? "-" : client.Client.Name }).ToList();
        }

        private void logOutButton_Click(object sender, EventArgs e)
        {
            _parent.Show();
            Close();
        }

        private void searchRideButton_Click(object sender, EventArgs e)
        {
            string destination = destinationTextBox.Text;
            DateTime departure = departureDateTimePicker.Value;
            refreshRides(_ctrl.FindRidesByDestinationAndDeparture(destination, departure));
        }

        private void clearFiltersButton_Click(object sender, EventArgs e)
        {
            refreshRides(_ctrl.FindAllRides());
        }

        private void ridesTable_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            if (e.RowIndex < 0)
            {
                return;
            }
            var selectedRidesRow = ridesTable.Rows[e.RowIndex];
            if (selectedRidesRow.Cells[0].Value.ToString() == "")
            {
                return;
            }
            string destination = selectedRidesRow.Cells[0].Value.ToString();
            DateTime departure = DateTime.Parse(selectedRidesRow.Cells[1].Value.ToString());
            selectedRide = _ctrl.FindRidesByDestinationAndDeparture(destination, departure)?[0];

            if (selectedRide == null)
            {
                return;
            }

            refreshClients(_ctrl.FindReservationsByRide(selectedRide));
        }

        private void reserveButton_Click(object sender, EventArgs e)
        {
            try
            {
                _ctrl.CreateReservation(selectedRide, clientNameTextBox.Text, clientPhoneTextBox.Text, int.Parse(noSeatsTextBox.Text));
            }
            catch(InvalidDataException ex)
            {
                MessageBox.Show(ex.Message, "Reservation Create Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            catch(FormatException)
            {
                MessageBox.Show("The number of seats should be a number!", "Reservation Create Error", MessageBoxButtons.OK, MessageBoxIcon.Error);

            }
        }
    }
}
