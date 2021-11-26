﻿using HelpdeskDAL;
using System;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace HelpdeskViewModels
{
    public class EmployeeViewModel
    {
        private readonly EmployeeDAO _dao;

        public string Title { get; set; }
        public string Firstname { get; set; }
        public string Lastname { get; set; }
        public string Email { get; set; }
        public string Phoneno { get; set; }
        public string Timer { get; set; }
        public int DepartmentID { get; set; }
        public string DepartmentName { get; set; }
        public int Id { get; set; }
        public bool isTech { get; set; }
        public string StaffPicture64 { get; set; }

        //constructor
        public EmployeeViewModel()
        {
            _dao = new EmployeeDAO();
        }

        //find Employee using Email property

        public async Task GetByEmail()
        {
            
            try
            {
                Employee emp = await _dao.GetbyEmail(Email);
                Title = emp.Title;
                Firstname = emp.FirstName;
                Lastname = emp.LastName;
                Phoneno = emp.PhoneNo;
                Email = emp.Email;
                Id = emp.Id;
                DepartmentID = emp.DepartmentId;
                if (emp.StaffPicture != null)
                {
                    StaffPicture64 = Convert.ToBase64String(emp.StaffPicture);
                }
                Timer = Convert.ToBase64String(emp.Timer);
            }
            catch (NullReferenceException nex)
            {
                Debug.WriteLine(nex.Message);
                Lastname = "not found";
            }
            catch (Exception ex)
            {
                Lastname = "not found";
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
        }

        public async Task GetById()
        {
            try
            {
                Employee emp = await _dao.GetById(Id);
                Title = emp.Title;
                Firstname = emp.FirstName;
                Lastname = emp.LastName;
                Phoneno = emp.PhoneNo;
                Email = emp.Email;
                Id = emp.Id;
                DepartmentID = emp.DepartmentId;
                if (emp.StaffPicture != null)
                {
                    StaffPicture64 = Convert.ToBase64String(emp.StaffPicture);
                }
                Timer = Convert.ToBase64String(emp.Timer);
            }
            catch (NullReferenceException nex)
            {
                Debug.WriteLine(nex.Message);
                Lastname = "not found";
            }
            catch (Exception ex)
            {
                Lastname = "not found";
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
        }


        //Retrieve all the Employees
        public async Task<List<EmployeeViewModel>> GetAll()
        {
            List<EmployeeViewModel> allVms = new List<EmployeeViewModel>();
            try
            {
                List<Employee> allEmployees = await _dao.GetAll();
                foreach (Employee emp in allEmployees)
                {
                    EmployeeViewModel empVm = new EmployeeViewModel
                    {
                        Title = emp.Title,
                        Firstname = emp.FirstName,
                        Lastname = emp.LastName,
                        Phoneno = emp.PhoneNo,
                        Email = emp.Email,
                        Id = emp.Id,
                        DepartmentID = emp.DepartmentId,
                        DepartmentName = emp.Department.DepartmentName,
                        Timer = Convert.ToBase64String(emp.Timer)
                    };
                    if (emp.StaffPicture != null)
                    {
                        empVm.StaffPicture64 = Convert.ToBase64String(emp.StaffPicture);
                    }
                    allVms.Add(empVm);
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return allVms;
        }

        //By the time we hit this method, all of the properties inside this EmployeeViewModel object will be filled
        public async Task Add()
        {
            Id = -1;
            try
            {
                Employee emp = new Employee
                {
                    Title = Title,
                    FirstName = Firstname,
                    LastName = Lastname,
                    PhoneNo = Phoneno,
                    Email = Email,
                    DepartmentId = DepartmentID
                };
                Id = await _dao.Add(emp);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
        }

        public async Task<int> Update()
        {
            UpdateStatus status = UpdateStatus.Failed;
            try
            {
                Employee emp = new Employee
                {
                    Title = Title,
                    FirstName = Firstname,
                    LastName = Lastname,
                    PhoneNo = Phoneno,
                    Id = Id,
                    Email = Email,
                    DepartmentId = DepartmentID
                };
                if (StaffPicture64 != null)
                {
                    emp.StaffPicture = Convert.FromBase64String(StaffPicture64);
                }
                emp.Timer = Convert.FromBase64String(Timer);
                status = await _dao.Update(emp);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return Convert.ToInt16(status);
        }

        public async Task<int> Delete()
        {
            int EmployeeDeleted = -1;
            try
            {
                EmployeeDeleted = await _dao.Delete(this.Id);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw;
            }
            return EmployeeDeleted;
        }
    }
}

