using HelpdeskDAL;
using System;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;
using System.Collections.Generic;

namespace HelpdeskViewModels
{
    public class ProblemViewModel
    {
        private ProblemDAO _dao;


        public int Id { get; set; }

        public string Description { get; set; }

        public string Timer { get; set; }


        //constructor
        public ProblemViewModel()
        {
            _dao = new ProblemDAO();
        }
        public async Task<List<ProblemViewModel>> GetAll()
        {
            List<ProblemViewModel> allVms = new List<ProblemViewModel>();
            try
            {
                List<Problem> allProblems = await _dao.GetAll();
                foreach (Problem problem in allProblems)
                {
                    ProblemViewModel empVm = new ProblemViewModel
                    {
                        Id = problem.Id,
                        Description = problem.Description,
                        Timer = Convert.ToBase64String(problem.Timer)
                    };
                
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
        //find Problem using Lastname property

        public async Task GetByDescription()
        {
            try
            {
                Problem problem = await _dao.GetByDescription(Description);
             
                Id = problem.Id;
                Description = problem.Description;
                Timer = Convert.ToBase64String(problem.Timer);


            }
            catch (Exception ex)
            {
                Debug.WriteLine("Problem in " + GetType().Name + " " + MethodBase.GetCurrentMethod().Name + " " + ex.Message);
                throw ex;
            }
        }
    }
}

