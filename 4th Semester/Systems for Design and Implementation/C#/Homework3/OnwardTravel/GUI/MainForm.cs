using OnwardTravel.Models;
using OnwardTravel.Service;
using OnwardTravel.Service.Exceptions;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Windows.Forms;

namespace OnwardTravel.GUI
{
    internal partial class MainForm : Form
    {
        private Form _parent;
        private UserService _service;
        private User _user;
        private Ride selectedRide = null;

        public MainForm()
        {
            InitializeComponent();
            designTable(ridesTable);
            designTable(clientsTable);
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

        public void SetParent(Form parent)
        {
            _parent = parent;
        }

        public void SetService(UserService service)
        {
            _service = service;
            refreshRides(service.FindAllRides());
        }

        public void SetUser(User user)
        {
            _user = user;
            welcomeLabel.Text = $"Welcome, {_user.Username}!";
        }

        public void refreshRides(IList<Ride> rides)
        {
            ridesTable.DataSource = rides.Select(ride => new { Destination = ride.Destination, Departure = ride.Departure, AvailableSeats = _service.FindEmptySeatsOnRide(ride) }).ToList();
        }

        public void refreshClients(ClientSeatDTO[] clients)
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
            refreshRides(_service.FindRidesByDestinationAndDeparture(destination, departure));
        }

        private void clearFiltersButton_Click(object sender, EventArgs e)
        {
            refreshRides(_service.FindAllRides());
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
            selectedRide = _service.FindRidesByDestinationAndDeparture(destination, departure)?[0];

            if (selectedRide == null)
            {
                return;
            }

            refreshClients(_service.FindReservationsByRide(selectedRide));
        }

        private void reserveButton_Click(object sender, EventArgs e)
        {
            try
            {
                _service.CreateReservation(selectedRide, clientNameTextBox.Text, clientPhoneTextBox.Text, int.Parse(noSeatsTextBox.Text));
                refreshClients(_service.FindReservationsByRide(selectedRide));
                refreshRides(_service.FindAllRides());
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
