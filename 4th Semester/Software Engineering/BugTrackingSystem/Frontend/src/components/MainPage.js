import React, { useState, useEffect } from 'react';
import { AppBar, Toolbar, Typography, Drawer, List, ListItem, ListItemIcon,  ListItemText } from '@material-ui/core';
import { Dashboard, Settings, BugReport, Assignment, ExitToApp } from '@material-ui/icons';
import { useNavigate } from 'react-router-dom';
import ManageAccountsPage from './ManageAccountsPage';
import BugsListPage from "./BugsListPage";
import SubmittedBugsPage from "./SubmittedBugsPage";
import AssignedBugsPage from "./AssignedBugsPage";

export default function MainPage() {
  const navigate = useNavigate();
  const [employee, setEmployee] = useState(null);
  const [mainComponent, setMainComponent] = useState(null);

  useEffect( () => {
    (async () => {
      await fetch('/api/employee-credentials')
        .then((response) => {
          if (!response.ok) {
            navigate('/login', {replace: true});
          }
          return response.json();
        })
        .then((data) => {
          setEmployee(data);
          setMainComponent(<BugsListPage employee={data} />)
        });
    })();
  }, []);

  const handleLogout = () => {
    fetch('/api/employee-credentials', { method: 'DELETE' })
      .then((response) => {
        if (response.ok) {
          navigate('/login', {replace: true});
        }
      });
  }

  return (
    <div className='mainRoot'>
      <AppBar className='mainAppBar'>
        <Toolbar className='flex-container unselectable'>
          <Typography variant='h6' className='occupy-space' unselectable='on'>
            Bug Tracking System
          </Typography>
            {employee ?
                <Typography variant='body1' unselectable='on'>
                    logged as <strong>{ employee['username'] }</strong>
                </Typography> : null
            }
        </Toolbar>
      </AppBar>
      <Drawer
        className='mainDrawer'
        variant='permanent'
        classes={{
          paper: 'drawerPaper'
        }}
      >
        <Toolbar />
        <div className='mainDrawerContainer'>
          <List>
             {employee ?
                 <ListItem button onClick={() => setMainComponent(<BugsListPage employee={employee} />)}>
                     <ListItemIcon>
                         <Dashboard />
                     </ListItemIcon>
                     <ListItemText primary='Bugs List' />
                 </ListItem> : null}
            {employee && employee['type'] === 'administrator' ?
                <ListItem button onClick={() => setMainComponent(<ManageAccountsPage />)}>
                  <ListItemIcon>
                    <Settings />
                  </ListItemIcon>
                  <ListItemText primary='Manage Accounts' />
                </ListItem> : null
            }
            {employee && employee['type'] === 'tester' ?
                <ListItem button onClick={() => setMainComponent(<SubmittedBugsPage />)}>
                  <ListItemIcon>
                    <BugReport />
                  </ListItemIcon>
                  <ListItemText primary='Submitted Bugs'/>
                </ListItem> : null
            }
            {employee && employee['type'] === 'programmer' ?
                <ListItem button onClick={() => setMainComponent(<AssignedBugsPage />)}>
                  <ListItemIcon>
                    <Assignment />
                  </ListItemIcon>
                  <ListItemText primary='Your Assignments' />
                </ListItem> : null
            }
          </List>
          <List>
            <ListItem button onClick={handleLogout}>
              <ListItemIcon>
                <ExitToApp />
              </ListItemIcon>
              <ListItemText primary='Logout' />
            </ListItem>
          </List>
        </div>
      </Drawer>
      <main className='mainContent'>
        <Toolbar />
          {mainComponent}
      </main>
    </div>
  );
}
